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
struct fs {char const* path; } ;

/* Variables and functions */
 scalar_t__ fs__check_mounts (struct fs*) ; 
 scalar_t__ fs__env_override (struct fs*) ; 
 scalar_t__ fs__read_mounts (struct fs*) ; 

__attribute__((used)) static const char *fs__get_mountpoint(struct fs *fs)
{
	if (fs__env_override(fs))
		return fs->path;

	if (fs__check_mounts(fs))
		return fs->path;

	if (fs__read_mounts(fs))
		return fs->path;

	return NULL;
}