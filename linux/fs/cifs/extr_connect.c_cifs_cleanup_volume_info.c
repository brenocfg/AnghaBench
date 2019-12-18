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
struct smb_vol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cifs_cleanup_volume_info_contents (struct smb_vol*) ; 
 int /*<<< orphan*/  kfree (struct smb_vol*) ; 

void
cifs_cleanup_volume_info(struct smb_vol *volume_info)
{
	if (!volume_info)
		return;
	cifs_cleanup_volume_info_contents(volume_info);
	kfree(volume_info);
}