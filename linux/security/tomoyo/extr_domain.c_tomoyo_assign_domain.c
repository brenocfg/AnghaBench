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
struct tomoyo_request_info {int granted; } ;
struct tomoyo_domain_info {size_t profile; int /*<<< orphan*/  group; int /*<<< orphan*/  domainname; int /*<<< orphan*/  list; int /*<<< orphan*/  acl_info_list; TYPE_1__* ns; } ;
typedef  int /*<<< orphan*/  e ;
struct TYPE_2__ {int /*<<< orphan*/ * profile_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int TOMOYO_EXEC_TMPSIZE ; 
 int /*<<< orphan*/  TOMOYO_MAC_FILE_EXECUTE ; 
 int TOMOYO_MAX_ACL_GROUPS ; 
 int /*<<< orphan*/  TOMOYO_STAT_POLICY_UPDATES ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* tomoyo_assign_namespace (char const*) ; 
 struct tomoyo_domain_info* tomoyo_commit_ok (struct tomoyo_domain_info*,int) ; 
 int /*<<< orphan*/  tomoyo_correct_domain (char const*) ; 
 struct tomoyo_domain_info* tomoyo_domain () ; 
 int /*<<< orphan*/  tomoyo_domain_list ; 
 struct tomoyo_domain_info* tomoyo_find_domain (char const*) ; 
 int /*<<< orphan*/  tomoyo_get_name (char const*) ; 
 int /*<<< orphan*/  tomoyo_init_request_info (struct tomoyo_request_info*,struct tomoyo_domain_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ tomoyo_namespace_jump (char const*) ; 
 scalar_t__ tomoyo_policy_loaded ; 
 int /*<<< orphan*/  tomoyo_policy_lock ; 
 int /*<<< orphan*/  tomoyo_put_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tomoyo_update_stat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tomoyo_write_log (struct tomoyo_request_info*,char*,int) ; 

struct tomoyo_domain_info *tomoyo_assign_domain(const char *domainname,
						const bool transit)
{
	struct tomoyo_domain_info e = { };
	struct tomoyo_domain_info *entry = tomoyo_find_domain(domainname);
	bool created = false;

	if (entry) {
		if (transit) {
			/*
			 * Since namespace is created at runtime, profiles may
			 * not be created by the moment the process transits to
			 * that domain. Do not perform domain transition if
			 * profile for that domain is not yet created.
			 */
			if (tomoyo_policy_loaded &&
			    !entry->ns->profile_ptr[entry->profile])
				return NULL;
		}
		return entry;
	}
	/* Requested domain does not exist. */
	/* Don't create requested domain if domainname is invalid. */
	if (strlen(domainname) >= TOMOYO_EXEC_TMPSIZE - 10 ||
	    !tomoyo_correct_domain(domainname))
		return NULL;
	/*
	 * Since definition of profiles and acl_groups may differ across
	 * namespaces, do not inherit "use_profile" and "use_group" settings
	 * by automatically creating requested domain upon domain transition.
	 */
	if (transit && tomoyo_namespace_jump(domainname))
		return NULL;
	e.ns = tomoyo_assign_namespace(domainname);
	if (!e.ns)
		return NULL;
	/*
	 * "use_profile" and "use_group" settings for automatically created
	 * domains are inherited from current domain. These are 0 for manually
	 * created domains.
	 */
	if (transit) {
		const struct tomoyo_domain_info *domain = tomoyo_domain();

		e.profile = domain->profile;
		memcpy(e.group, domain->group, sizeof(e.group));
	}
	e.domainname = tomoyo_get_name(domainname);
	if (!e.domainname)
		return NULL;
	if (mutex_lock_interruptible(&tomoyo_policy_lock))
		goto out;
	entry = tomoyo_find_domain(domainname);
	if (!entry) {
		entry = tomoyo_commit_ok(&e, sizeof(e));
		if (entry) {
			INIT_LIST_HEAD(&entry->acl_info_list);
			list_add_tail_rcu(&entry->list, &tomoyo_domain_list);
			created = true;
		}
	}
	mutex_unlock(&tomoyo_policy_lock);
out:
	tomoyo_put_name(e.domainname);
	if (entry && transit) {
		if (created) {
			struct tomoyo_request_info r;
			int i;

			tomoyo_init_request_info(&r, entry,
						 TOMOYO_MAC_FILE_EXECUTE);
			r.granted = false;
			tomoyo_write_log(&r, "use_profile %u\n",
					 entry->profile);
			for (i = 0; i < TOMOYO_MAX_ACL_GROUPS; i++)
				if (test_bit(i, entry->group))
					tomoyo_write_log(&r, "use_group %u\n",
							 i);
			tomoyo_update_stat(TOMOYO_STAT_POLICY_UPDATES);
		}
	}
	return entry;
}