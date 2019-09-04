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
struct task_struct {int dummy; } ;
struct TYPE_2__ {struct task_struct* kswapd; } ;

/* Variables and functions */
 TYPE_1__* NODE_DATA (int) ; 
 int /*<<< orphan*/  kthread_stop (struct task_struct*) ; 

void kswapd_stop(int nid)
{
	struct task_struct *kswapd = NODE_DATA(nid)->kswapd;

	if (kswapd) {
		kthread_stop(kswapd);
		NODE_DATA(nid)->kswapd = NULL;
	}
}