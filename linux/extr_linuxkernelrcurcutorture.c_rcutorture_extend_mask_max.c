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
struct TYPE_2__ {int extendables; } ;

/* Variables and functions */
 int RCUTORTURE_MAX_EXTEND ; 
 int RCUTORTURE_RDR_RCU ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 TYPE_1__* cur_ops ; 
 int extendables ; 

__attribute__((used)) static int rcutorture_extend_mask_max(void)
{
	int mask;

	WARN_ON_ONCE(extendables & ~RCUTORTURE_MAX_EXTEND);
	mask = extendables & RCUTORTURE_MAX_EXTEND & cur_ops->extendables;
	mask = mask | RCUTORTURE_RDR_RCU;
	return mask;
}