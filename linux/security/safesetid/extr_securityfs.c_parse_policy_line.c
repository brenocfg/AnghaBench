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
typedef  int /*<<< orphan*/  u32 ;
struct setuid_rule {void* dst_uid; void* src_uid; } ;
struct file {TYPE_1__* f_cred; } ;
struct TYPE_2__ {int /*<<< orphan*/  user_ns; } ;

/* Variables and functions */
 int EINVAL ; 
 int kstrtou32 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* make_kuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  uid_valid (void*) ; 

__attribute__((used)) static int parse_policy_line(struct file *file, char *buf,
	struct setuid_rule *rule)
{
	char *child_str;
	int ret;
	u32 parsed_parent, parsed_child;

	/* Format of |buf| string should be <UID>:<UID>. */
	child_str = strchr(buf, ':');
	if (child_str == NULL)
		return -EINVAL;
	*child_str = '\0';
	child_str++;

	ret = kstrtou32(buf, 0, &parsed_parent);
	if (ret)
		return ret;

	ret = kstrtou32(child_str, 0, &parsed_child);
	if (ret)
		return ret;

	rule->src_uid = make_kuid(file->f_cred->user_ns, parsed_parent);
	rule->dst_uid = make_kuid(file->f_cred->user_ns, parsed_child);
	if (!uid_valid(rule->src_uid) || !uid_valid(rule->dst_uid))
		return -EINVAL;

	return 0;
}