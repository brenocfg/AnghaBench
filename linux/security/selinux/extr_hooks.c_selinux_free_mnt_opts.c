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
struct selinux_mnt_opts {struct selinux_mnt_opts* defcontext; struct selinux_mnt_opts* rootcontext; struct selinux_mnt_opts* context; struct selinux_mnt_opts* fscontext; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct selinux_mnt_opts*) ; 

__attribute__((used)) static void selinux_free_mnt_opts(void *mnt_opts)
{
	struct selinux_mnt_opts *opts = mnt_opts;
	kfree(opts->fscontext);
	kfree(opts->context);
	kfree(opts->rootcontext);
	kfree(opts->defcontext);
	kfree(opts);
}