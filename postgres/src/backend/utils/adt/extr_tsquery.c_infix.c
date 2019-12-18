#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int int8 ;
typedef  int int16 ;
struct TYPE_7__ {scalar_t__ oper; int distance; } ;
struct TYPE_8__ {int distance; int length; int weight; scalar_t__ prefix; } ;
struct TYPE_10__ {scalar_t__ type; TYPE_1__ qoperator; TYPE_2__ qoperand; } ;
struct TYPE_9__ {char* op; char* cur; int buflen; char* buf; TYPE_6__* curpol; } ;
typedef  TYPE_2__ QueryOperand ;
typedef  TYPE_3__ INFIX ;

/* Variables and functions */
 int /*<<< orphan*/  COPYCHAR (char*,char*) ; 
 int /*<<< orphan*/  ERROR ; 
#define  OP_AND 130 
 scalar_t__ OP_NOT ; 
#define  OP_OR 129 
#define  OP_PHRASE 128 
 scalar_t__ QI_VAL ; 
 int QO_PRIORITY (TYPE_6__*) ; 
 int /*<<< orphan*/  RESIZEBUF (TYPE_3__*,int) ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int pg_database_encoding_max_length () ; 
 int pg_mblen (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 void* strchr (char*,char) ; 
 scalar_t__ t_iseq (char*,char) ; 

__attribute__((used)) static void
infix(INFIX *in, int parentPriority, bool rightPhraseOp)
{
	/* since this function recurses, it could be driven to stack overflow. */
	check_stack_depth();

	if (in->curpol->type == QI_VAL)
	{
		QueryOperand *curpol = &in->curpol->qoperand;
		char	   *op = in->op + curpol->distance;
		int			clen;

		RESIZEBUF(in, curpol->length * (pg_database_encoding_max_length() + 1) + 2 + 6);
		*(in->cur) = '\'';
		in->cur++;
		while (*op)
		{
			if (t_iseq(op, '\''))
			{
				*(in->cur) = '\'';
				in->cur++;
			}
			else if (t_iseq(op, '\\'))
			{
				*(in->cur) = '\\';
				in->cur++;
			}
			COPYCHAR(in->cur, op);

			clen = pg_mblen(op);
			op += clen;
			in->cur += clen;
		}
		*(in->cur) = '\'';
		in->cur++;
		if (curpol->weight || curpol->prefix)
		{
			*(in->cur) = ':';
			in->cur++;
			if (curpol->prefix)
			{
				*(in->cur) = '*';
				in->cur++;
			}
			if (curpol->weight & (1 << 3))
			{
				*(in->cur) = 'A';
				in->cur++;
			}
			if (curpol->weight & (1 << 2))
			{
				*(in->cur) = 'B';
				in->cur++;
			}
			if (curpol->weight & (1 << 1))
			{
				*(in->cur) = 'C';
				in->cur++;
			}
			if (curpol->weight & 1)
			{
				*(in->cur) = 'D';
				in->cur++;
			}
		}
		*(in->cur) = '\0';
		in->curpol++;
	}
	else if (in->curpol->qoperator.oper == OP_NOT)
	{
		int			priority = QO_PRIORITY(in->curpol);

		if (priority < parentPriority)
		{
			RESIZEBUF(in, 2);
			sprintf(in->cur, "( ");
			in->cur = strchr(in->cur, '\0');
		}
		RESIZEBUF(in, 1);
		*(in->cur) = '!';
		in->cur++;
		*(in->cur) = '\0';
		in->curpol++;

		infix(in, priority, false);
		if (priority < parentPriority)
		{
			RESIZEBUF(in, 2);
			sprintf(in->cur, " )");
			in->cur = strchr(in->cur, '\0');
		}
	}
	else
	{
		int8		op = in->curpol->qoperator.oper;
		int			priority = QO_PRIORITY(in->curpol);
		int16		distance = in->curpol->qoperator.distance;
		INFIX		nrm;
		bool		needParenthesis = false;

		in->curpol++;
		if (priority < parentPriority ||
		/* phrase operator depends on order */
			(op == OP_PHRASE && rightPhraseOp))
		{
			needParenthesis = true;
			RESIZEBUF(in, 2);
			sprintf(in->cur, "( ");
			in->cur = strchr(in->cur, '\0');
		}

		nrm.curpol = in->curpol;
		nrm.op = in->op;
		nrm.buflen = 16;
		nrm.cur = nrm.buf = (char *) palloc(sizeof(char) * nrm.buflen);

		/* get right operand */
		infix(&nrm, priority, (op == OP_PHRASE));

		/* get & print left operand */
		in->curpol = nrm.curpol;
		infix(in, priority, false);

		/* print operator & right operand */
		RESIZEBUF(in, 3 + (2 + 10 /* distance */ ) + (nrm.cur - nrm.buf));
		switch (op)
		{
			case OP_OR:
				sprintf(in->cur, " | %s", nrm.buf);
				break;
			case OP_AND:
				sprintf(in->cur, " & %s", nrm.buf);
				break;
			case OP_PHRASE:
				if (distance != 1)
					sprintf(in->cur, " <%d> %s", distance, nrm.buf);
				else
					sprintf(in->cur, " <-> %s", nrm.buf);
				break;
			default:
				/* OP_NOT is handled in above if-branch */
				elog(ERROR, "unrecognized operator type: %d", op);
		}
		in->cur = strchr(in->cur, '\0');
		pfree(nrm.buf);

		if (needParenthesis)
		{
			RESIZEBUF(in, 2);
			sprintf(in->cur, " )");
			in->cur = strchr(in->cur, '\0');
		}
	}
}