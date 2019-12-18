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
struct smb_vol {scalar_t__ sectype; char* username; char* password; int /*<<< orphan*/  nullauth; int /*<<< orphan*/  cred_uid; } ;
struct cifs_ses {int sectype; int /*<<< orphan*/ * password; int /*<<< orphan*/ * user_name; int /*<<< orphan*/  cred_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_MAX_PASSWORD_LEN ; 
 int /*<<< orphan*/  CIFS_MAX_USERNAME_LEN ; 
#define  Kerberos 128 
 scalar_t__ Unspecified ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int match_session(struct cifs_ses *ses, struct smb_vol *vol)
{
	if (vol->sectype != Unspecified &&
	    vol->sectype != ses->sectype)
		return 0;

	switch (ses->sectype) {
	case Kerberos:
		if (!uid_eq(vol->cred_uid, ses->cred_uid))
			return 0;
		break;
	default:
		/* NULL username means anonymous session */
		if (ses->user_name == NULL) {
			if (!vol->nullauth)
				return 0;
			break;
		}

		/* anything else takes username/password */
		if (strncmp(ses->user_name,
			    vol->username ? vol->username : "",
			    CIFS_MAX_USERNAME_LEN))
			return 0;
		if ((vol->username && strlen(vol->username) != 0) &&
		    ses->password != NULL &&
		    strncmp(ses->password,
			    vol->password ? vol->password : "",
			    CIFS_MAX_PASSWORD_LEN))
			return 0;
	}
	return 1;
}