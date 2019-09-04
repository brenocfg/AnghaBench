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
struct fs_path {scalar_t__ buf; scalar_t__ inline_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct fs_path*) ; 

__attribute__((used)) static void fs_path_free(struct fs_path *p)
{
	if (!p)
		return;
	if (p->buf != p->inline_buf)
		kfree(p->buf);
	kfree(p);
}