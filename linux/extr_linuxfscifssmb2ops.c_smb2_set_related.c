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
struct smb_rqst {TYPE_1__* rq_iov; } ;
struct smb2_sync_hdr {int /*<<< orphan*/  Flags; } ;
struct TYPE_2__ {scalar_t__ iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMB2_FLAGS_RELATED_OPERATIONS ; 

__attribute__((used)) static void
smb2_set_related(struct smb_rqst *rqst)
{
	struct smb2_sync_hdr *shdr;

	shdr = (struct smb2_sync_hdr *)(rqst->rq_iov[0].iov_base);
	shdr->Flags |= SMB2_FLAGS_RELATED_OPERATIONS;
}