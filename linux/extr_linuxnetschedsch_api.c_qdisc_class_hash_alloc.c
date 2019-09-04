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
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (struct hlist_head*) ; 
 struct hlist_head* kvmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct hlist_head *qdisc_class_hash_alloc(unsigned int n)
{
	struct hlist_head *h;
	unsigned int i;

	h = kvmalloc_array(n, sizeof(struct hlist_head), GFP_KERNEL);

	if (h != NULL) {
		for (i = 0; i < n; i++)
			INIT_HLIST_HEAD(&h[i]);
	}
	return h;
}