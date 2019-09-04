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
struct win_version_info {int major; int minor; int build; int revis; } ;
typedef  int /*<<< orphan*/  config_t ;

/* Variables and functions */
 scalar_t__ config_get_int (int /*<<< orphan*/ *,char const*,char*) ; 

__attribute__((used)) static inline bool config_ver_mismatch(
		config_t *ver_config,
		const char *section,
		struct win_version_info *ver)
{
	struct win_version_info config_ver;
	bool mismatch = false;

#define get_sub_ver(subver) \
	config_ver.subver = (int)config_get_int(ver_config, section, #subver); \
	mismatch |= config_ver.subver != ver->subver;

	get_sub_ver(major);
	get_sub_ver(minor);
	get_sub_ver(build);
	get_sub_ver(revis);

#undef get_sub_ver

	return mismatch;
}