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
struct cred {struct user_namespace* user_ns; void* cap_bset; void* cap_ambient; void* cap_effective; void* cap_permitted; void* cap_inheritable; int /*<<< orphan*/  securebits; } ;

/* Variables and functions */
 void* CAP_EMPTY_SET ; 
 void* CAP_FULL_SET ; 
 int /*<<< orphan*/  SECUREBITS_DEFAULT ; 

__attribute__((used)) static void set_cred_user_ns(struct cred *cred, struct user_namespace *user_ns)
{
	/* Start with the same capabilities as init but useless for doing
	 * anything as the capabilities are bound to the new user namespace.
	 */
	cred->securebits = SECUREBITS_DEFAULT;
	cred->cap_inheritable = CAP_EMPTY_SET;
	cred->cap_permitted = CAP_FULL_SET;
	cred->cap_effective = CAP_FULL_SET;
	cred->cap_ambient = CAP_EMPTY_SET;
	cred->cap_bset = CAP_FULL_SET;
#ifdef CONFIG_KEYS
	key_put(cred->request_key_auth);
	cred->request_key_auth = NULL;
#endif
	/* tgcred will be cleared in our caller bc CLONE_THREAD won't be set */
	cred->user_ns = user_ns;
}