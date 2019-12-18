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
struct smb_vol {scalar_t__ sectype; } ;
struct cifs_ses {scalar_t__ sectype; } ;

/* Variables and functions */
 scalar_t__ Kerberos ; 
 int cifs_set_cifscreds (struct smb_vol*,struct cifs_ses*) ; 

__attribute__((used)) static int
cifs_set_vol_auth(struct smb_vol *vol, struct cifs_ses *ses)
{
	vol->sectype = ses->sectype;

	/* krb5 is special, since we don't need username or pw */
	if (vol->sectype == Kerberos)
		return 0;

	return cifs_set_cifscreds(vol, ses);
}