#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tomoyo_profile {int /*<<< orphan*/ * pref; struct tomoyo_path_info const* comment; } ;
typedef  struct tomoyo_path_info const tomoyo_path_info ;
struct TYPE_3__ {TYPE_2__* ns; } ;
struct tomoyo_io_buffer {char* write_buf; TYPE_1__ w; } ;
struct TYPE_4__ {int /*<<< orphan*/  profile_version; } ;
typedef  int /*<<< orphan*/  DEFINE_SPINLOCK ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 unsigned int TOMOYO_MAX_PREF ; 
 unsigned int simple_strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int sscanf (char*,char*,int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 struct tomoyo_profile* tomoyo_assign_profile (TYPE_2__*,unsigned int) ; 
 struct tomoyo_path_info const* tomoyo_get_name (char*) ; 
 int /*<<< orphan*/ * tomoyo_pref_keywords ; 
 int /*<<< orphan*/  tomoyo_put_name (struct tomoyo_path_info const*) ; 
 int tomoyo_set_mode (char*,char*,struct tomoyo_profile*) ; 
 int /*<<< orphan*/  tomoyo_set_uint (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tomoyo_write_profile(struct tomoyo_io_buffer *head)
{
	char *data = head->write_buf;
	unsigned int i;
	char *cp;
	struct tomoyo_profile *profile;

	if (sscanf(data, "PROFILE_VERSION=%u", &head->w.ns->profile_version)
	    == 1)
		return 0;
	i = simple_strtoul(data, &cp, 10);
	if (*cp != '-')
		return -EINVAL;
	data = cp + 1;
	profile = tomoyo_assign_profile(head->w.ns, i);
	if (!profile)
		return -EINVAL;
	cp = strchr(data, '=');
	if (!cp)
		return -EINVAL;
	*cp++ = '\0';
	if (!strcmp(data, "COMMENT")) {
		static DEFINE_SPINLOCK(lock);
		const struct tomoyo_path_info *new_comment
			= tomoyo_get_name(cp);
		const struct tomoyo_path_info *old_comment;

		if (!new_comment)
			return -ENOMEM;
		spin_lock(&lock);
		old_comment = profile->comment;
		profile->comment = new_comment;
		spin_unlock(&lock);
		tomoyo_put_name(old_comment);
		return 0;
	}
	if (!strcmp(data, "PREFERENCE")) {
		for (i = 0; i < TOMOYO_MAX_PREF; i++)
			tomoyo_set_uint(&profile->pref[i], cp,
					tomoyo_pref_keywords[i]);
		return 0;
	}
	return tomoyo_set_mode(data, cp, profile);
}