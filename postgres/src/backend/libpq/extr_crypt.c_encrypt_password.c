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
typedef  scalar_t__ PasswordType ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MD5_PASSWD_LEN ; 
#define  PASSWORD_TYPE_MD5 130 
#define  PASSWORD_TYPE_PLAINTEXT 129 
#define  PASSWORD_TYPE_SCRAM_SHA_256 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ get_password_type (char const*) ; 
 char* palloc (int /*<<< orphan*/ ) ; 
 char* pg_be_scram_build_secret (char const*) ; 
 int /*<<< orphan*/  pg_md5_encrypt (char const*,char const*,int /*<<< orphan*/ ,char*) ; 
 char* pstrdup (char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

char *
encrypt_password(PasswordType target_type, const char *role,
				 const char *password)
{
	PasswordType guessed_type = get_password_type(password);
	char	   *encrypted_password;

	if (guessed_type != PASSWORD_TYPE_PLAINTEXT)
	{
		/*
		 * Cannot convert an already-encrypted password from one format to
		 * another, so return it as it is.
		 */
		return pstrdup(password);
	}

	switch (target_type)
	{
		case PASSWORD_TYPE_MD5:
			encrypted_password = palloc(MD5_PASSWD_LEN + 1);

			if (!pg_md5_encrypt(password, role, strlen(role),
								encrypted_password))
				elog(ERROR, "password encryption failed");
			return encrypted_password;

		case PASSWORD_TYPE_SCRAM_SHA_256:
			return pg_be_scram_build_secret(password);

		case PASSWORD_TYPE_PLAINTEXT:
			elog(ERROR, "cannot encrypt password with 'plaintext'");
	}

	/*
	 * This shouldn't happen, because the above switch statements should
	 * handle every combination of source and target password types.
	 */
	elog(ERROR, "cannot encrypt password to requested type");
	return NULL;				/* keep compiler quiet */
}