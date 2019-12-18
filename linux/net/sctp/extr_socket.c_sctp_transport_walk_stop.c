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
struct rhashtable_iter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rhashtable_walk_exit (struct rhashtable_iter*) ; 
 int /*<<< orphan*/  rhashtable_walk_stop (struct rhashtable_iter*) ; 

void sctp_transport_walk_stop(struct rhashtable_iter *iter)
{
	rhashtable_walk_stop(iter);
	rhashtable_walk_exit(iter);
}