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
struct fs_path {int /*<<< orphan*/  buf_len; int /*<<< orphan*/  inline_buf; int /*<<< orphan*/  buf; scalar_t__ reversed; } ;

/* Variables and functions */
 int /*<<< orphan*/  FS_PATH_INLINE_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  fs_path_reset (struct fs_path*) ; 
 struct fs_path* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fs_path *fs_path_alloc(void)
{
	struct fs_path *p;

	p = kmalloc(sizeof(*p), GFP_KERNEL);
	if (!p)
		return NULL;
	p->reversed = 0;
	p->buf = p->inline_buf;
	p->buf_len = FS_PATH_INLINE_SIZE;
	fs_path_reset(p);
	return p;
}