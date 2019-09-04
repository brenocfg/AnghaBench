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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ stat (char const*,struct stat*) ; 

__attribute__((used)) static inline bool is_dir(const char *path)
{
	struct stat stat_info;
	if (stat(path, &stat_info) == 0)
		return !!S_ISDIR(stat_info.st_mode);

	blog(LOG_DEBUG, "is_dir: stat for %s failed, errno: %d", path, errno);
	return false;
}