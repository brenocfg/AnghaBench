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
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CRACKLIB_DICTPATH ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FascistCheck (char const*,int /*<<< orphan*/ ) ; 
 int MIN_PWD_LENGTH ; 
 scalar_t__ PASSWORD_TYPE_PLAINTEXT ; 
 scalar_t__ STATUS_OK ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ isalpha (unsigned char) ; 
 scalar_t__ plain_crypt_verify (char const*,char const*,char const*,char**) ; 
 int /*<<< orphan*/  prev_check_password_hook (char const*,char const*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int strlen (char const*) ; 
 scalar_t__ strstr (char const*,char const*) ; 

__attribute__((used)) static void
check_password(const char *username,
			   const char *shadow_pass,
			   PasswordType password_type,
			   Datum validuntil_time,
			   bool validuntil_null)
{
	if (prev_check_password_hook)
		prev_check_password_hook(username, shadow_pass,
								 password_type, validuntil_time,
								 validuntil_null);

	if (password_type != PASSWORD_TYPE_PLAINTEXT)
	{
		/*
		 * Unfortunately we cannot perform exhaustive checks on encrypted
		 * passwords - we are restricted to guessing. (Alternatively, we could
		 * insist on the password being presented non-encrypted, but that has
		 * its own security disadvantages.)
		 *
		 * We only check for username = password.
		 */
		char	   *logdetail;

		if (plain_crypt_verify(username, shadow_pass, username, &logdetail) == STATUS_OK)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("password must not equal user name")));
	}
	else
	{
		/*
		 * For unencrypted passwords we can perform better checks
		 */
		const char *password = shadow_pass;
		int			pwdlen = strlen(password);
		int			i;
		bool		pwd_has_letter,
					pwd_has_nonletter;

		/* enforce minimum length */
		if (pwdlen < MIN_PWD_LENGTH)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("password is too short")));

		/* check if the password contains the username */
		if (strstr(password, username))
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("password must not contain user name")));

		/* check if the password contains both letters and non-letters */
		pwd_has_letter = false;
		pwd_has_nonletter = false;
		for (i = 0; i < pwdlen; i++)
		{
			/*
			 * isalpha() does not work for multibyte encodings but let's
			 * consider non-ASCII characters non-letters
			 */
			if (isalpha((unsigned char) password[i]))
				pwd_has_letter = true;
			else
				pwd_has_nonletter = true;
		}
		if (!pwd_has_letter || !pwd_has_nonletter)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("password must contain both letters and nonletters")));

#ifdef USE_CRACKLIB
		/* call cracklib to check password */
		if (FascistCheck(password, CRACKLIB_DICTPATH))
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("password is easily cracked")));
#endif
	}

	/* all checks passed, password is ok */
}