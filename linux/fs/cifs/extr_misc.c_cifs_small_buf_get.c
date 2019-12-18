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
struct smb_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cifs_sm_req_poolp ; 
 struct smb_hdr* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smBufAllocCount ; 
 int /*<<< orphan*/  totSmBufAllocCount ; 

struct smb_hdr *
cifs_small_buf_get(void)
{
	struct smb_hdr *ret_buf = NULL;

/* We could use negotiated size instead of max_msgsize -
   but it may be more efficient to always alloc same size
   albeit slightly larger than necessary and maxbuffersize
   defaults to this and can not be bigger */
	ret_buf = mempool_alloc(cifs_sm_req_poolp, GFP_NOFS);
	/* No need to clear memory here, cleared in header assemble */
	/*	memset(ret_buf, 0, sizeof(struct smb_hdr) + 27);*/
	atomic_inc(&smBufAllocCount);
#ifdef CONFIG_CIFS_STATS2
	atomic_inc(&totSmBufAllocCount);
#endif /* CONFIG_CIFS_STATS2 */

	return ret_buf;
}