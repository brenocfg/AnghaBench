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
struct pid_namespace {int /*<<< orphan*/  proc_mnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  kern_unmount (int /*<<< orphan*/ ) ; 

void pid_ns_release_proc(struct pid_namespace *ns)
{
	kern_unmount(ns->proc_mnt);
}