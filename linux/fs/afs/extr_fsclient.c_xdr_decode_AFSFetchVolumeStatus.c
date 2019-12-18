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
struct afs_volume_status {scalar_t__ vol_backup_date; scalar_t__ vol_copy_date; void* part_max_blocks; void* part_blocks_avail; void* blocks_in_use; void* max_quota; void* min_quota; void* type; void* needs_salvage; void* blessed; void* in_service; void* online; void* parent_id; void* vid; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 void* ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xdr_decode_AFSFetchVolumeStatus(const __be32 **_bp,
					    struct afs_volume_status *vs)
{
	const __be32 *bp = *_bp;

	vs->vid			= ntohl(*bp++);
	vs->parent_id		= ntohl(*bp++);
	vs->online		= ntohl(*bp++);
	vs->in_service		= ntohl(*bp++);
	vs->blessed		= ntohl(*bp++);
	vs->needs_salvage	= ntohl(*bp++);
	vs->type		= ntohl(*bp++);
	vs->min_quota		= ntohl(*bp++);
	vs->max_quota		= ntohl(*bp++);
	vs->blocks_in_use	= ntohl(*bp++);
	vs->part_blocks_avail	= ntohl(*bp++);
	vs->part_max_blocks	= ntohl(*bp++);
	vs->vol_copy_date	= 0;
	vs->vol_backup_date	= 0;
	*_bp = bp;
}