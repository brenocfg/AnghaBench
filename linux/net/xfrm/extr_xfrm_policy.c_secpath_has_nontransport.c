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
struct sec_path {int len; TYPE_2__** xvec; } ;
struct TYPE_3__ {scalar_t__ mode; } ;
struct TYPE_4__ {TYPE_1__ props; } ;

/* Variables and functions */
 scalar_t__ XFRM_MODE_TRANSPORT ; 

__attribute__((used)) static inline int secpath_has_nontransport(const struct sec_path *sp, int k, int *idxp)
{
	for (; k < sp->len; k++) {
		if (sp->xvec[k]->props.mode != XFRM_MODE_TRANSPORT) {
			*idxp = k;
			return 1;
		}
	}

	return 0;
}