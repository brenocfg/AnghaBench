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
struct file {int /*<<< orphan*/  f_cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_OPT_NONE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cap_valid (int) ; 
 scalar_t__ security_capable (int /*<<< orphan*/ ,struct user_namespace*,int,int /*<<< orphan*/ ) ; 

bool file_ns_capable(const struct file *file, struct user_namespace *ns,
		     int cap)
{

	if (WARN_ON_ONCE(!cap_valid(cap)))
		return false;

	if (security_capable(file->f_cred, ns, cap, CAP_OPT_NONE) == 0)
		return true;

	return false;
}