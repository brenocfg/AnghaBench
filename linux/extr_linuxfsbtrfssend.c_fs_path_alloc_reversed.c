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
struct fs_path {int reversed; } ;

/* Variables and functions */
 struct fs_path* fs_path_alloc () ; 
 int /*<<< orphan*/  fs_path_reset (struct fs_path*) ; 

__attribute__((used)) static struct fs_path *fs_path_alloc_reversed(void)
{
	struct fs_path *p;

	p = fs_path_alloc();
	if (!p)
		return NULL;
	p->reversed = 1;
	fs_path_reset(p);
	return p;
}