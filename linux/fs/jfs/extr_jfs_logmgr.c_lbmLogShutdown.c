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
struct lbuf {int /*<<< orphan*/  l_page; struct lbuf* l_freelist; } ;
struct jfs_log {struct lbuf* lbuf_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jfs_info (char*,struct jfs_log*) ; 
 int /*<<< orphan*/  kfree (struct lbuf*) ; 

__attribute__((used)) static void lbmLogShutdown(struct jfs_log * log)
{
	struct lbuf *lbuf;

	jfs_info("lbmLogShutdown: log:0x%p", log);

	lbuf = log->lbuf_free;
	while (lbuf) {
		struct lbuf *next = lbuf->l_freelist;
		__free_page(lbuf->l_page);
		kfree(lbuf);
		lbuf = next;
	}
}