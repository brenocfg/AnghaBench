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
typedef  scalar_t__ u8 ;
struct tomoyo_policy_namespace {scalar_t__* profile_ptr; } ;
struct TYPE_2__ {int is_delete; struct tomoyo_domain_info* domain; } ;
struct tomoyo_io_buffer {char* write_buf; TYPE_1__ w; } ;
struct tomoyo_domain_info {int* flags; int /*<<< orphan*/  acl_info_list; int /*<<< orphan*/  group; scalar_t__ profile; struct tomoyo_policy_namespace* ns; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int TOMOYO_MAX_ACL_GROUPS ; 
 unsigned int TOMOYO_MAX_DOMAIN_INFO_FLAGS ; 
 unsigned int TOMOYO_MAX_PROFILES ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int sscanf (char*,char*,unsigned int*) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,scalar_t__) ; 
 struct tomoyo_domain_info* tomoyo_assign_domain (char*,int) ; 
 int tomoyo_delete_domain (char*) ; 
 char** tomoyo_dif ; 
 struct tomoyo_domain_info* tomoyo_find_domain (char*) ; 
 int /*<<< orphan*/  tomoyo_policy_loaded ; 
 scalar_t__ tomoyo_str_starts (char**,char*) ; 
 int tomoyo_write_domain2 (struct tomoyo_policy_namespace*,int /*<<< orphan*/ *,char*,int const) ; 

__attribute__((used)) static int tomoyo_write_domain(struct tomoyo_io_buffer *head)
{
	char *data = head->write_buf;
	struct tomoyo_policy_namespace *ns;
	struct tomoyo_domain_info *domain = head->w.domain;
	const bool is_delete = head->w.is_delete;
	bool is_select = !is_delete && tomoyo_str_starts(&data, "select ");
	unsigned int idx;

	if (*data == '<') {
		int ret = 0;

		domain = NULL;
		if (is_delete)
			ret = tomoyo_delete_domain(data);
		else if (is_select)
			domain = tomoyo_find_domain(data);
		else
			domain = tomoyo_assign_domain(data, false);
		head->w.domain = domain;
		return ret;
	}
	if (!domain)
		return -EINVAL;
	ns = domain->ns;
	if (sscanf(data, "use_profile %u", &idx) == 1
	    && idx < TOMOYO_MAX_PROFILES) {
		if (!tomoyo_policy_loaded || ns->profile_ptr[idx])
			if (!is_delete)
				domain->profile = (u8) idx;
		return 0;
	}
	if (sscanf(data, "use_group %u\n", &idx) == 1
	    && idx < TOMOYO_MAX_ACL_GROUPS) {
		if (!is_delete)
			set_bit(idx, domain->group);
		else
			clear_bit(idx, domain->group);
		return 0;
	}
	for (idx = 0; idx < TOMOYO_MAX_DOMAIN_INFO_FLAGS; idx++) {
		const char *cp = tomoyo_dif[idx];

		if (strncmp(data, cp, strlen(cp) - 1))
			continue;
		domain->flags[idx] = !is_delete;
		return 0;
	}
	return tomoyo_write_domain2(ns, &domain->acl_info_list, data,
				    is_delete);
}