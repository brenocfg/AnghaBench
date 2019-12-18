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
struct fs {char const* path; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ fs__check_mounts (struct fs*) ; 
 struct fs* fs__entries ; 
 scalar_t__ fs__mountpoint (int) ; 
 scalar_t__ mount (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* mount_overload (struct fs*) ; 

__attribute__((used)) static const char *fs__mount(int idx)
{
	struct fs *fs = &fs__entries[idx];
	const char *mountpoint;

	if (fs__mountpoint(idx))
		return (const char *)fs->path;

	mountpoint = mount_overload(fs);

	if (mount(NULL, mountpoint, fs->name, 0, NULL) < 0)
		return NULL;

	return fs__check_mounts(fs) ? fs->path : NULL;
}