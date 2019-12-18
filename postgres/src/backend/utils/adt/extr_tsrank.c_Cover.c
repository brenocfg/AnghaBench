#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int pos; scalar_t__ p; scalar_t__ q; TYPE_2__* begin; TYPE_2__* end; } ;
struct TYPE_11__ {int /*<<< orphan*/  pos; } ;
struct TYPE_10__ {int /*<<< orphan*/  query; } ;
typedef  TYPE_1__ QueryRepresentation ;
typedef  TYPE_2__ DocRepresentation ;
typedef  TYPE_3__ CoverExt ;

/* Variables and functions */
 int /*<<< orphan*/  GETQUERY (int /*<<< orphan*/ ) ; 
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  TS_EXEC_CALC_NOT ; 
 int /*<<< orphan*/  TS_EXEC_EMPTY ; 
 scalar_t__ TS_execute (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ WEP_GETPOS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/  checkcondition_QueryOperand ; 
 int /*<<< orphan*/  fillQueryRepresentationData (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  resetQueryRepresentation (TYPE_1__*,int) ; 

__attribute__((used)) static bool
Cover(DocRepresentation *doc, int len, QueryRepresentation *qr, CoverExt *ext)
{
	DocRepresentation *ptr;
	int			lastpos = ext->pos;
	bool		found = false;

	/*
	 * since this function recurses, it could be driven to stack overflow.
	 * (though any decent compiler will optimize away the tail-recursion.
	 */
	check_stack_depth();

	resetQueryRepresentation(qr, false);

	ext->p = INT_MAX;
	ext->q = 0;
	ptr = doc + ext->pos;

	/* find upper bound of cover from current position, move up */
	while (ptr - doc < len)
	{
		fillQueryRepresentationData(qr, ptr);

		if (TS_execute(GETQUERY(qr->query), (void *) qr,
					   TS_EXEC_EMPTY, checkcondition_QueryOperand))
		{
			if (WEP_GETPOS(ptr->pos) > ext->q)
			{
				ext->q = WEP_GETPOS(ptr->pos);
				ext->end = ptr;
				lastpos = ptr - doc;
				found = true;
			}
			break;
		}
		ptr++;
	}

	if (!found)
		return false;

	resetQueryRepresentation(qr, true);

	ptr = doc + lastpos;

	/* find lower bound of cover from found upper bound, move down */
	while (ptr >= doc + ext->pos)
	{
		/*
		 * we scan doc from right to left, so pos info in reverse order!
		 */
		fillQueryRepresentationData(qr, ptr);

		if (TS_execute(GETQUERY(qr->query), (void *) qr,
					   TS_EXEC_CALC_NOT, checkcondition_QueryOperand))
		{
			if (WEP_GETPOS(ptr->pos) < ext->p)
			{
				ext->begin = ptr;
				ext->p = WEP_GETPOS(ptr->pos);
			}
			break;
		}
		ptr--;
	}

	if (ext->p <= ext->q)
	{
		/*
		 * set position for next try to next lexeme after beginning of found
		 * cover
		 */
		ext->pos = (ptr - doc) + 1;
		return true;
	}

	ext->pos++;
	return Cover(doc, len, qr, ext);
}