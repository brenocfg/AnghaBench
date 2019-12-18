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
struct TYPE_2__ {int /*<<< orphan*/  count; } ;
struct net {TYPE_1__ ct; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nf_ct_unconfirmed_destroy (struct net*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  nf_queue_nf_hook_drop (struct net*) ; 
 int /*<<< orphan*/  synchronize_net () ; 

void nf_ct_unconfirmed_destroy(struct net *net)
{
	might_sleep();

	if (atomic_read(&net->ct.count) > 0) {
		__nf_ct_unconfirmed_destroy(net);
		nf_queue_nf_hook_drop(net);
		synchronize_net();
	}
}