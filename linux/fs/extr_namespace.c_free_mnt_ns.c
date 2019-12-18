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
struct mnt_namespace {int /*<<< orphan*/  user_ns; int /*<<< orphan*/  ucounts; int /*<<< orphan*/  ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  dec_mnt_namespaces (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_anon_ns (struct mnt_namespace*) ; 
 int /*<<< orphan*/  kfree (struct mnt_namespace*) ; 
 int /*<<< orphan*/  ns_free_inum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_user_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_mnt_ns(struct mnt_namespace *ns)
{
	if (!is_anon_ns(ns))
		ns_free_inum(&ns->ns);
	dec_mnt_namespaces(ns->ucounts);
	put_user_ns(ns->user_ns);
	kfree(ns);
}