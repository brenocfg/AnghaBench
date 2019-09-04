#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cifs_tcon {int share_flags; TYPE_2__* ses; scalar_t__ seal; } ;
struct TYPE_4__ {int session_flags; TYPE_1__* server; } ;
struct TYPE_3__ {int capabilities; } ;

/* Variables and functions */
 int SHI1005_FLAGS_ENCRYPT_DATA ; 
 int SMB2_GLOBAL_CAP_ENCRYPTION ; 
 int SMB2_SESSION_FLAG_ENCRYPT_DATA ; 

int smb3_encryption_required(const struct cifs_tcon *tcon)
{
	if (!tcon)
		return 0;
	if ((tcon->ses->session_flags & SMB2_SESSION_FLAG_ENCRYPT_DATA) ||
	    (tcon->share_flags & SHI1005_FLAGS_ENCRYPT_DATA))
		return 1;
	if (tcon->seal &&
	    (tcon->ses->server->capabilities & SMB2_GLOBAL_CAP_ENCRYPTION))
		return 1;
	return 0;
}