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

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  MD5_PASSWD_LEN ; 
 scalar_t__ PASSWORD_TYPE_MD5 ; 
 int STATUS_ERROR ; 
 int STATUS_OK ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ get_password_type (char const*) ; 
 int /*<<< orphan*/  pg_md5_encrypt (char const*,char const*,int,char*) ; 
 char* psprintf (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char*) ; 

int
md5_crypt_verify(const char *role, const char *shadow_pass,
				 const char *client_pass,
				 const char *md5_salt, int md5_salt_len,
				 char **logdetail)
{
	int			retval;
	char		crypt_pwd[MD5_PASSWD_LEN + 1];

	Assert(md5_salt_len > 0);

	if (get_password_type(shadow_pass) != PASSWORD_TYPE_MD5)
	{
		/* incompatible password hash format. */
		*logdetail = psprintf(_("User \"%s\" has a password that cannot be used with MD5 authentication."),
							  role);
		return STATUS_ERROR;
	}

	/*
	 * Compute the correct answer for the MD5 challenge.
	 *
	 * We do not bother setting logdetail for any pg_md5_encrypt failure
	 * below: the only possible error is out-of-memory, which is unlikely, and
	 * if it did happen adding a psprintf call would only make things worse.
	 */
	/* stored password already encrypted, only do salt */
	if (!pg_md5_encrypt(shadow_pass + strlen("md5"),
						md5_salt, md5_salt_len,
						crypt_pwd))
	{
		return STATUS_ERROR;
	}

	if (strcmp(client_pass, crypt_pwd) == 0)
		retval = STATUS_OK;
	else
	{
		*logdetail = psprintf(_("Password does not match for user \"%s\"."),
							  role);
		retval = STATUS_ERROR;
	}

	return retval;
}