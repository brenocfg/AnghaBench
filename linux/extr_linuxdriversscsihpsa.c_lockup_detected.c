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
typedef  int /*<<< orphan*/  u32 ;
struct ctlr_info {int /*<<< orphan*/  lockup_detected; } ;

/* Variables and functions */
 int get_cpu () ; 
 int /*<<< orphan*/ * per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_cpu () ; 

__attribute__((used)) static u32 lockup_detected(struct ctlr_info *h)
{
	int cpu;
	u32 rc, *lockup_detected;

	cpu = get_cpu();
	lockup_detected = per_cpu_ptr(h->lockup_detected, cpu);
	rc = *lockup_detected;
	put_cpu();
	return rc;
}