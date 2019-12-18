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
struct smb2_file_all_info {int /*<<< orphan*/  IndexNumber; } ;
struct create_on_disk_id {int /*<<< orphan*/  DiskFileId; int /*<<< orphan*/  VolumeId; } ;
struct create_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
parse_query_id_ctxt(struct create_context *cc, struct smb2_file_all_info *buf)
{
	struct create_on_disk_id *pdisk_id = (struct create_on_disk_id *)cc;

	cifs_dbg(FYI, "parse query id context 0x%llx 0x%llx\n",
		pdisk_id->DiskFileId, pdisk_id->VolumeId);
	buf->IndexNumber = pdisk_id->DiskFileId;
}