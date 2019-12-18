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
 void put_ipc_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_ipc_ns (struct ns_common*) ; 

__attribute__((used)) static void ipcns_put(struct ns_common *ns)
{
	return put_ipc_ns(to_ipc_ns(ns));
}