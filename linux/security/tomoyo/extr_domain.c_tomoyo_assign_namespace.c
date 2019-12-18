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
struct tomoyo_policy_namespace {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int TOMOYO_EXEC_TMPSIZE ; 
 int /*<<< orphan*/  kfree (struct tomoyo_policy_namespace*) ; 
 struct tomoyo_policy_namespace* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (char*,char const*,unsigned int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tomoyo_domain_def (char const*) ; 
 struct tomoyo_policy_namespace* tomoyo_find_namespace (char const*,unsigned int) ; 
 int /*<<< orphan*/  tomoyo_init_policy_namespace (struct tomoyo_policy_namespace*) ; 
 scalar_t__ tomoyo_memory_ok (struct tomoyo_policy_namespace*) ; 
 int /*<<< orphan*/  tomoyo_policy_lock ; 

struct tomoyo_policy_namespace *tomoyo_assign_namespace(const char *domainname)
{
	struct tomoyo_policy_namespace *ptr;
	struct tomoyo_policy_namespace *entry;
	const char *cp = domainname;
	unsigned int len = 0;

	while (*cp && *cp++ != ' ')
		len++;
	ptr = tomoyo_find_namespace(domainname, len);
	if (ptr)
		return ptr;
	if (len >= TOMOYO_EXEC_TMPSIZE - 10 || !tomoyo_domain_def(domainname))
		return NULL;
	entry = kzalloc(sizeof(*entry) + len + 1, GFP_NOFS);
	if (!entry)
		return NULL;
	if (mutex_lock_interruptible(&tomoyo_policy_lock))
		goto out;
	ptr = tomoyo_find_namespace(domainname, len);
	if (!ptr && tomoyo_memory_ok(entry)) {
		char *name = (char *) (entry + 1);

		ptr = entry;
		memmove(name, domainname, len);
		name[len] = '\0';
		entry->name = name;
		tomoyo_init_policy_namespace(entry);
		entry = NULL;
	}
	mutex_unlock(&tomoyo_policy_lock);
out:
	kfree(entry);
	return ptr;
}