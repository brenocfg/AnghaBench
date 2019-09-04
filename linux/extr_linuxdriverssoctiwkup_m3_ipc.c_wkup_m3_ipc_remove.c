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
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rproc; int /*<<< orphan*/  mbox; } ;

/* Variables and functions */
 TYPE_1__* m3_ipc_state ; 
 int /*<<< orphan*/  mbox_free_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rproc_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rproc_shutdown (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wkup_m3_ipc_remove(struct platform_device *pdev)
{
	mbox_free_channel(m3_ipc_state->mbox);

	rproc_shutdown(m3_ipc_state->rproc);
	rproc_put(m3_ipc_state->rproc);

	m3_ipc_state = NULL;

	return 0;
}