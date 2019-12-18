#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32 ;
struct TYPE_6__ {char* cur; int buflen; char* buf; TYPE_1__* curpol; } ;
struct TYPE_5__ {scalar_t__ type; int val; } ;
typedef  TYPE_2__ INFIX ;

/* Variables and functions */
 scalar_t__ OPR ; 
 int /*<<< orphan*/  RESIZEBUF (TYPE_2__*,int) ; 
 scalar_t__ VAL ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 void* strchr (char*,char) ; 

__attribute__((used)) static void
infix(INFIX *in, bool first)
{
	/* since this function recurses, it could be driven to stack overflow. */
	check_stack_depth();

	if (in->curpol->type == VAL)
	{
		RESIZEBUF(in, 11);
		sprintf(in->cur, "%d", in->curpol->val);
		in->cur = strchr(in->cur, '\0');
		in->curpol--;
	}
	else if (in->curpol->val == (int32) '!')
	{
		bool		isopr = false;

		RESIZEBUF(in, 1);
		*(in->cur) = '!';
		in->cur++;
		*(in->cur) = '\0';
		in->curpol--;
		if (in->curpol->type == OPR)
		{
			isopr = true;
			RESIZEBUF(in, 2);
			sprintf(in->cur, "( ");
			in->cur = strchr(in->cur, '\0');
		}
		infix(in, isopr);
		if (isopr)
		{
			RESIZEBUF(in, 2);
			sprintf(in->cur, " )");
			in->cur = strchr(in->cur, '\0');
		}
	}
	else
	{
		int32		op = in->curpol->val;
		INFIX		nrm;

		in->curpol--;
		if (op == (int32) '|' && !first)
		{
			RESIZEBUF(in, 2);
			sprintf(in->cur, "( ");
			in->cur = strchr(in->cur, '\0');
		}

		nrm.curpol = in->curpol;
		nrm.buflen = 16;
		nrm.cur = nrm.buf = (char *) palloc(sizeof(char) * nrm.buflen);

		/* get right operand */
		infix(&nrm, false);

		/* get & print left operand */
		in->curpol = nrm.curpol;
		infix(in, false);

		/* print operator & right operand */
		RESIZEBUF(in, 3 + (nrm.cur - nrm.buf));
		sprintf(in->cur, " %c %s", op, nrm.buf);
		in->cur = strchr(in->cur, '\0');
		pfree(nrm.buf);

		if (op == (int32) '|' && !first)
		{
			RESIZEBUF(in, 2);
			sprintf(in->cur, " )");
			in->cur = strchr(in->cur, '\0');
		}
	}
}