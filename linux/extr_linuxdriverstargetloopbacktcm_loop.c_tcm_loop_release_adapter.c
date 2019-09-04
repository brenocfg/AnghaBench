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
struct tcm_loop_hba {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tcm_loop_hba*) ; 
 struct tcm_loop_hba* to_tcm_loop_hba (struct device*) ; 

__attribute__((used)) static void tcm_loop_release_adapter(struct device *dev)
{
	struct tcm_loop_hba *tl_hba = to_tcm_loop_hba(dev);

	kfree(tl_hba);
}