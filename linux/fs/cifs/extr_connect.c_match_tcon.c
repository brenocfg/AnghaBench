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
struct smb_vol {scalar_t__ seal; scalar_t__ snapshot_time; scalar_t__ handle_timeout; scalar_t__ no_lease; int /*<<< orphan*/  UNC; } ;
struct cifs_tcon {scalar_t__ tidStatus; scalar_t__ seal; scalar_t__ snapshot_time; scalar_t__ handle_timeout; scalar_t__ no_lease; int /*<<< orphan*/  treeName; } ;

/* Variables and functions */
 scalar_t__ CifsExiting ; 
 int /*<<< orphan*/  MAX_TREE_SIZE ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int match_tcon(struct cifs_tcon *tcon, struct smb_vol *volume_info)
{
	if (tcon->tidStatus == CifsExiting)
		return 0;
	if (strncmp(tcon->treeName, volume_info->UNC, MAX_TREE_SIZE))
		return 0;
	if (tcon->seal != volume_info->seal)
		return 0;
	if (tcon->snapshot_time != volume_info->snapshot_time)
		return 0;
	if (tcon->handle_timeout != volume_info->handle_timeout)
		return 0;
	if (tcon->no_lease != volume_info->no_lease)
		return 0;
	return 1;
}