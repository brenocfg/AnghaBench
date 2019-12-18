#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  fh_pad; } ;
struct knfsd_fh {scalar_t__ fh_size; TYPE_1__ fh_base; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline bool fh_match(struct knfsd_fh *fh1, struct knfsd_fh *fh2)
{
	if (fh1->fh_size != fh2->fh_size)
		return false;
	if (memcmp(fh1->fh_base.fh_pad, fh2->fh_base.fh_pad, fh1->fh_size) != 0)
		return false;
	return true;
}