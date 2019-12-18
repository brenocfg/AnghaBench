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
struct net_device {int dummy; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int __bpf_offload_dev_match (struct bpf_prog*,struct net_device*) ; 
 int /*<<< orphan*/  bpf_devs_lock ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

bool bpf_offload_dev_match(struct bpf_prog *prog, struct net_device *netdev)
{
	bool ret;

	down_read(&bpf_devs_lock);
	ret = __bpf_offload_dev_match(prog, netdev);
	up_read(&bpf_devs_lock);

	return ret;
}