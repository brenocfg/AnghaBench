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
struct user_namespace {int dummy; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int cred_has_capability (struct cred const*,int,unsigned int,int) ; 
 struct user_namespace init_user_ns ; 

__attribute__((used)) static int selinux_capable(const struct cred *cred, struct user_namespace *ns,
			   int cap, unsigned int opts)
{
	return cred_has_capability(cred, cap, opts, ns == &init_user_ns);
}