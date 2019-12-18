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
struct netlink_callback {int (* done ) (struct netlink_callback*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  fib6_dump_end (struct netlink_callback*) ; 
 int stub1 (struct netlink_callback*) ; 

__attribute__((used)) static int fib6_dump_done(struct netlink_callback *cb)
{
	fib6_dump_end(cb);
	return cb->done ? cb->done(cb) : 0;
}