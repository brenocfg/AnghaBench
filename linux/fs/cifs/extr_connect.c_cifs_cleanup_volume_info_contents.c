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
struct smb_vol {int /*<<< orphan*/  prepath; int /*<<< orphan*/  iocharset; int /*<<< orphan*/  domainname; int /*<<< orphan*/  UNC; int /*<<< orphan*/  password; int /*<<< orphan*/  username; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ ) ; 

void
cifs_cleanup_volume_info_contents(struct smb_vol *volume_info)
{
	kfree(volume_info->username);
	kzfree(volume_info->password);
	kfree(volume_info->UNC);
	kfree(volume_info->domainname);
	kfree(volume_info->iocharset);
	kfree(volume_info->prepath);
}