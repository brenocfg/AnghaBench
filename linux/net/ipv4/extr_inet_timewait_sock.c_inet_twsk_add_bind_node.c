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
struct inet_timewait_sock {int /*<<< orphan*/  tw_bind_node; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,struct hlist_head*) ; 

__attribute__((used)) static void inet_twsk_add_bind_node(struct inet_timewait_sock *tw,
				    struct hlist_head *list)
{
	hlist_add_head(&tw->tw_bind_node, list);
}