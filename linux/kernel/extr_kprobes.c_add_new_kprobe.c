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
struct kprobe {scalar_t__ post_handler; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 scalar_t__ aggr_post_handler ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unoptimize_kprobe (struct kprobe*,int) ; 

__attribute__((used)) static int add_new_kprobe(struct kprobe *ap, struct kprobe *p)
{
	if (p->post_handler)
		unoptimize_kprobe(ap, true);	/* Fall back to normal kprobe */

	list_add_rcu(&p->list, &ap->list);
	if (p->post_handler && !ap->post_handler)
		ap->post_handler = aggr_post_handler;

	return 0;
}