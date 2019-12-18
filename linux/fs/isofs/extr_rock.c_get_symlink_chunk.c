#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct SL_component {int flags; int len; int /*<<< orphan*/  text; } ;
struct TYPE_3__ {int flags; struct SL_component link; } ;
struct TYPE_4__ {TYPE_1__ SL; } ;
struct rock_ridge {int len; TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*,int) ; 

__attribute__((used)) static char *get_symlink_chunk(char *rpnt, struct rock_ridge *rr, char *plimit)
{
	int slen;
	int rootflag;
	struct SL_component *oldslp;
	struct SL_component *slp;
	slen = rr->len - 5;
	slp = &rr->u.SL.link;
	while (slen > 1) {
		rootflag = 0;
		switch (slp->flags & ~1) {
		case 0:
			if (slp->len > plimit - rpnt)
				return NULL;
			memcpy(rpnt, slp->text, slp->len);
			rpnt += slp->len;
			break;
		case 2:
			if (rpnt >= plimit)
				return NULL;
			*rpnt++ = '.';
			break;
		case 4:
			if (2 > plimit - rpnt)
				return NULL;
			*rpnt++ = '.';
			*rpnt++ = '.';
			break;
		case 8:
			if (rpnt >= plimit)
				return NULL;
			rootflag = 1;
			*rpnt++ = '/';
			break;
		default:
			printk("Symlink component flag not implemented (%d)\n",
			       slp->flags);
		}
		slen -= slp->len + 2;
		oldslp = slp;
		slp = (struct SL_component *)((char *)slp + slp->len + 2);

		if (slen < 2) {
			/*
			 * If there is another SL record, and this component
			 * record isn't continued, then add a slash.
			 */
			if ((!rootflag) && (rr->u.SL.flags & 1) &&
			    !(oldslp->flags & 1)) {
				if (rpnt >= plimit)
					return NULL;
				*rpnt++ = '/';
			}
			break;
		}

		/*
		 * If this component record isn't continued, then append a '/'.
		 */
		if (!rootflag && !(oldslp->flags & 1)) {
			if (rpnt >= plimit)
				return NULL;
			*rpnt++ = '/';
		}
	}
	return rpnt;
}