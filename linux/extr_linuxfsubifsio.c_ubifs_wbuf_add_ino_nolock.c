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
struct ubifs_wbuf {int /*<<< orphan*/  lock; int /*<<< orphan*/  next_ino; int /*<<< orphan*/ * inodes; scalar_t__ used; int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ubifs_wbuf_add_ino_nolock(struct ubifs_wbuf *wbuf, ino_t inum)
{
	if (!wbuf->buf)
		/* NOR flash or something similar */
		return;

	spin_lock(&wbuf->lock);
	if (wbuf->used)
		wbuf->inodes[wbuf->next_ino++] = inum;
	spin_unlock(&wbuf->lock);
}