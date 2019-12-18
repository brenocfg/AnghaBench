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
struct fs_path {int /*<<< orphan*/  reversed; } ;

/* Variables and functions */
 int fs_path_add_path (struct fs_path*,struct fs_path*) ; 
 int /*<<< orphan*/  fs_path_reset (struct fs_path*) ; 

__attribute__((used)) static int fs_path_copy(struct fs_path *p, struct fs_path *from)
{
	int ret;

	p->reversed = from->reversed;
	fs_path_reset(p);

	ret = fs_path_add_path(p, from);

	return ret;
}