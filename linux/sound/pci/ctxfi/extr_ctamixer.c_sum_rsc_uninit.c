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
struct sum {int /*<<< orphan*/  rsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  rsc_uninit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sum_rsc_uninit(struct sum *sum)
{
	rsc_uninit(&sum->rsc);
	return 0;
}