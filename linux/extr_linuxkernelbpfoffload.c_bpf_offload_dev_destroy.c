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
struct bpf_offload_dev {int /*<<< orphan*/  netdevs; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct bpf_offload_dev*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void bpf_offload_dev_destroy(struct bpf_offload_dev *offdev)
{
	WARN_ON(!list_empty(&offdev->netdevs));
	kfree(offdev);
}