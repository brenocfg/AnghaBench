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
struct ubifs_wbuf {int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  jhead; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ubifs_wbuf_sync_nolock (struct ubifs_wbuf*) ; 

__attribute__((used)) static inline int ubifs_wbuf_sync(struct ubifs_wbuf *wbuf)
{
	int err;

	mutex_lock_nested(&wbuf->io_mutex, wbuf->jhead);
	err = ubifs_wbuf_sync_nolock(wbuf);
	mutex_unlock(&wbuf->io_mutex);
	return err;
}