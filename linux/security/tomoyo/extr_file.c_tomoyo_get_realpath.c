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
struct tomoyo_path_info {scalar_t__ name; } ;
struct path {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tomoyo_fill_path_info (struct tomoyo_path_info*) ; 
 scalar_t__ tomoyo_realpath_from_path (struct path const*) ; 

__attribute__((used)) static bool tomoyo_get_realpath(struct tomoyo_path_info *buf, const struct path *path)
{
	buf->name = tomoyo_realpath_from_path(path);
	if (buf->name) {
		tomoyo_fill_path_info(buf);
		return true;
	}
	return false;
}