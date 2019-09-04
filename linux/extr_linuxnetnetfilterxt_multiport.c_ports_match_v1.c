#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u_int16_t ;
struct xt_multiport_v1 {unsigned int count; int flags; int invert; int /*<<< orphan*/ * ports; scalar_t__* pflags; } ;

/* Variables and functions */
#define  XT_MULTIPORT_DESTINATION 130 
#define  XT_MULTIPORT_EITHER 129 
#define  XT_MULTIPORT_SOURCE 128 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static inline bool
ports_match_v1(const struct xt_multiport_v1 *minfo,
	       u_int16_t src, u_int16_t dst)
{
	unsigned int i;
	u_int16_t s, e;

	for (i = 0; i < minfo->count; i++) {
		s = minfo->ports[i];

		if (minfo->pflags[i]) {
			/* range port matching */
			e = minfo->ports[++i];
			pr_debug("src or dst matches with %d-%d?\n", s, e);

			switch (minfo->flags) {
			case XT_MULTIPORT_SOURCE:
				if (src >= s && src <= e)
					return true ^ minfo->invert;
				break;
			case XT_MULTIPORT_DESTINATION:
				if (dst >= s && dst <= e)
					return true ^ minfo->invert;
				break;
			case XT_MULTIPORT_EITHER:
				if ((dst >= s && dst <= e) ||
				    (src >= s && src <= e))
					return true ^ minfo->invert;
				break;
			default:
				break;
			}
		} else {
			/* exact port matching */
			pr_debug("src or dst matches with %d?\n", s);

			switch (minfo->flags) {
			case XT_MULTIPORT_SOURCE:
				if (src == s)
					return true ^ minfo->invert;
				break;
			case XT_MULTIPORT_DESTINATION:
				if (dst == s)
					return true ^ minfo->invert;
				break;
			case XT_MULTIPORT_EITHER:
				if (src == s || dst == s)
					return true ^ minfo->invert;
				break;
			default:
				break;
			}
		}
	}

	return minfo->invert;
}