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
struct uts_namespace {int /*<<< orphan*/  user_ns; } ;
struct nsproxy {struct uts_namespace* uts_ns; } ;
struct ns_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EPERM ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  get_uts_ns (struct uts_namespace*) ; 
 int /*<<< orphan*/  ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_uts_ns (struct uts_namespace*) ; 
 struct uts_namespace* to_uts_ns (struct ns_common*) ; 

__attribute__((used)) static int utsns_install(struct nsproxy *nsproxy, struct ns_common *new)
{
	struct uts_namespace *ns = to_uts_ns(new);

	if (!ns_capable(ns->user_ns, CAP_SYS_ADMIN) ||
	    !ns_capable(current_user_ns(), CAP_SYS_ADMIN))
		return -EPERM;

	get_uts_ns(ns);
	put_uts_ns(nsproxy->uts_ns);
	nsproxy->uts_ns = ns;
	return 0;
}