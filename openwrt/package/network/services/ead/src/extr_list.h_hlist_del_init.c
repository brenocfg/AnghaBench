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
struct hlist_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HLIST_NODE (struct hlist_node*) ; 
 int /*<<< orphan*/  __hlist_del (struct hlist_node*) ; 
 int /*<<< orphan*/  hlist_unhashed (struct hlist_node*) ; 

__attribute__((used)) static inline void hlist_del_init(struct hlist_node *n)
{
	if (!hlist_unhashed(n)) {
		__hlist_del(n);
		INIT_HLIST_NODE(n);
	}
}