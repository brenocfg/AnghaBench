#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct smb_rqst {size_t rq_nvec; TYPE_1__* rq_iov; } ;
struct smb2_sync_hdr {int /*<<< orphan*/  NextCommand; } ;
struct TCP_Server_Info {int dummy; } ;
struct TYPE_2__ {int iov_len; scalar_t__ iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (unsigned long) ; 
 scalar_t__ smb2_padding ; 
 unsigned long smb_rqst_len (struct TCP_Server_Info*,struct smb_rqst*) ; 

__attribute__((used)) static void
smb2_set_next_command(struct TCP_Server_Info *server, struct smb_rqst *rqst)
{
	struct smb2_sync_hdr *shdr;
	unsigned long len = smb_rqst_len(server, rqst);

	/* SMB headers in a compound are 8 byte aligned. */
	if (len & 7) {
		rqst->rq_iov[rqst->rq_nvec].iov_base = smb2_padding;
		rqst->rq_iov[rqst->rq_nvec].iov_len = 8 - (len & 7);
		rqst->rq_nvec++;
		len = smb_rqst_len(server, rqst);
	}

	shdr = (struct smb2_sync_hdr *)(rqst->rq_iov[0].iov_base);
	shdr->NextCommand = cpu_to_le32(len);
}