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
struct gfs2_rbm {scalar_t__ rgd; scalar_t__ bii; scalar_t__ offset; } ;

/* Variables and functions */

__attribute__((used)) static inline bool gfs2_rbm_eq(const struct gfs2_rbm *rbm1,
			       const struct gfs2_rbm *rbm2)
{
	return (rbm1->rgd == rbm2->rgd) && (rbm1->bii == rbm2->bii) &&
	       (rbm1->offset == rbm2->offset);
}