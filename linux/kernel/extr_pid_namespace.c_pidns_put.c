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
struct ns_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_pid_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_pid_ns (struct ns_common*) ; 

__attribute__((used)) static void pidns_put(struct ns_common *ns)
{
	put_pid_ns(to_pid_ns(ns));
}