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
struct wkup_m3_ipc {int /*<<< orphan*/  rproc; int /*<<< orphan*/  sync_complete; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  do_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int rproc_boot (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wkup_m3_rproc_boot_thread(struct wkup_m3_ipc *m3_ipc)
{
	struct device *dev = m3_ipc->dev;
	int ret;

	init_completion(&m3_ipc->sync_complete);

	ret = rproc_boot(m3_ipc->rproc);
	if (ret)
		dev_err(dev, "rproc_boot failed\n");

	do_exit(0);
}