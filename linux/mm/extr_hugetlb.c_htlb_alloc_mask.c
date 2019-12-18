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
struct hstate {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_HIGHUSER ; 
 int /*<<< orphan*/  GFP_HIGHUSER_MOVABLE ; 
 scalar_t__ hugepage_movable_supported (struct hstate*) ; 

__attribute__((used)) static inline gfp_t htlb_alloc_mask(struct hstate *h)
{
	if (hugepage_movable_supported(h))
		return GFP_HIGHUSER_MOVABLE;
	else
		return GFP_HIGHUSER;
}