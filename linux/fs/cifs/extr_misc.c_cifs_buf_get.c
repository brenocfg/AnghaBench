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
struct smb2_sync_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bufAllocCount ; 
 int /*<<< orphan*/  cifs_req_poolp ; 
 struct smb_hdr* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct smb_hdr*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  totBufAllocCount ; 

struct smb_hdr *
cifs_buf_get(void)
{
	struct smb_hdr *ret_buf = NULL;
	/*
	 * SMB2 header is bigger than CIFS one - no problems to clean some
	 * more bytes for CIFS.
	 */
	size_t buf_size = sizeof(struct smb2_sync_hdr);

	/*
	 * We could use negotiated size instead of max_msgsize -
	 * but it may be more efficient to always alloc same size
	 * albeit slightly larger than necessary and maxbuffersize
	 * defaults to this and can not be bigger.
	 */
	ret_buf = mempool_alloc(cifs_req_poolp, GFP_NOFS);

	/* clear the first few header bytes */
	/* for most paths, more is cleared in header_assemble */
	memset(ret_buf, 0, buf_size + 3);
	atomic_inc(&bufAllocCount);
#ifdef CONFIG_CIFS_STATS2
	atomic_inc(&totBufAllocCount);
#endif /* CONFIG_CIFS_STATS2 */

	return ret_buf;
}