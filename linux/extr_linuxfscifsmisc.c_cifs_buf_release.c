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

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bufAllocCount ; 
 int /*<<< orphan*/  cifs_req_poolp ; 
 int /*<<< orphan*/  mempool_free (void*,int /*<<< orphan*/ ) ; 

void
cifs_buf_release(void *buf_to_free)
{
	if (buf_to_free == NULL) {
		/* cifs_dbg(FYI, "Null buffer passed to cifs_buf_release\n");*/
		return;
	}
	mempool_free(buf_to_free, cifs_req_poolp);

	atomic_dec(&bufAllocCount);
	return;
}