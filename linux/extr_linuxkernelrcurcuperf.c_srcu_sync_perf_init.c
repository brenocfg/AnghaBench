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

/* Variables and functions */
 int /*<<< orphan*/  init_srcu_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * srcu_ctlp ; 
 int /*<<< orphan*/  srcud ; 

__attribute__((used)) static void srcu_sync_perf_init(void)
{
	srcu_ctlp = &srcud;
	init_srcu_struct(srcu_ctlp);
}