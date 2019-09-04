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
struct win_version_info {int /*<<< orphan*/  revis; int /*<<< orphan*/  build; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
typedef  int /*<<< orphan*/  config_t ;

/* Variables and functions */
 int /*<<< orphan*/  config_set_int (int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void write_config_ver(config_t *ver_config, const char *section,
		struct win_version_info *ver)
{
#define set_sub_ver(subver) \
	config_set_int(ver_config, section, #subver, ver->subver);

	set_sub_ver(major);
	set_sub_ver(minor);
	set_sub_ver(build);
	set_sub_ver(revis);

#undef set_sub_ver
}