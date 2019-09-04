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
struct pipe_buffer {scalar_t__ len; } ;
struct fuse_copy_state {int /*<<< orphan*/ * pg; scalar_t__ write; struct pipe_buffer* currbuf; scalar_t__ len; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  flush_dcache_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_page_dirty_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fuse_copy_finish(struct fuse_copy_state *cs)
{
	if (cs->currbuf) {
		struct pipe_buffer *buf = cs->currbuf;

		if (cs->write)
			buf->len = PAGE_SIZE - cs->len;
		cs->currbuf = NULL;
	} else if (cs->pg) {
		if (cs->write) {
			flush_dcache_page(cs->pg);
			set_page_dirty_lock(cs->pg);
		}
		put_page(cs->pg);
	}
	cs->pg = NULL;
}