#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ubifs_info {int jhead_cnt; TYPE_2__* jheads; } ;
struct TYPE_3__ {TYPE_2__* inodes; TYPE_2__* buf; } ;
struct TYPE_4__ {struct TYPE_4__* log_hash; TYPE_1__ wbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 

__attribute__((used)) static void free_wbufs(struct ubifs_info *c)
{
	int i;

	if (c->jheads) {
		for (i = 0; i < c->jhead_cnt; i++) {
			kfree(c->jheads[i].wbuf.buf);
			kfree(c->jheads[i].wbuf.inodes);
			kfree(c->jheads[i].log_hash);
		}
		kfree(c->jheads);
		c->jheads = NULL;
	}
}