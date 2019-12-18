#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct tomoyo_profile {scalar_t__* pref; size_t* config; size_t default_config; } ;
struct tomoyo_policy_namespace {int dummy; } ;
struct tomoyo_acl_info {TYPE_1__* cond; } ;
struct TYPE_2__ {scalar_t__ grant_log; } ;

/* Variables and functions */
 size_t TOMOYO_CONFIG_USE_DEFAULT ; 
 size_t TOMOYO_CONFIG_WANT_GRANT_LOG ; 
 size_t TOMOYO_CONFIG_WANT_REJECT_LOG ; 
 scalar_t__ TOMOYO_GRANTLOG_AUTO ; 
 scalar_t__ TOMOYO_GRANTLOG_YES ; 
 size_t TOMOYO_MAX_MAC_INDEX ; 
 size_t TOMOYO_PREF_MAX_AUDIT_LOG ; 
 size_t* tomoyo_index2category ; 
 scalar_t__ tomoyo_log_count ; 
 int /*<<< orphan*/  tomoyo_policy_loaded ; 
 struct tomoyo_profile* tomoyo_profile (struct tomoyo_policy_namespace const*,size_t const) ; 

__attribute__((used)) static bool tomoyo_get_audit(const struct tomoyo_policy_namespace *ns,
			     const u8 profile, const u8 index,
			     const struct tomoyo_acl_info *matched_acl,
			     const bool is_granted)
{
	u8 mode;
	const u8 category = tomoyo_index2category[index] +
		TOMOYO_MAX_MAC_INDEX;
	struct tomoyo_profile *p;

	if (!tomoyo_policy_loaded)
		return false;
	p = tomoyo_profile(ns, profile);
	if (tomoyo_log_count >= p->pref[TOMOYO_PREF_MAX_AUDIT_LOG])
		return false;
	if (is_granted && matched_acl && matched_acl->cond &&
	    matched_acl->cond->grant_log != TOMOYO_GRANTLOG_AUTO)
		return matched_acl->cond->grant_log == TOMOYO_GRANTLOG_YES;
	mode = p->config[index];
	if (mode == TOMOYO_CONFIG_USE_DEFAULT)
		mode = p->config[category];
	if (mode == TOMOYO_CONFIG_USE_DEFAULT)
		mode = p->default_config;
	if (is_granted)
		return mode & TOMOYO_CONFIG_WANT_GRANT_LOG;
	return mode & TOMOYO_CONFIG_WANT_REJECT_LOG;
}