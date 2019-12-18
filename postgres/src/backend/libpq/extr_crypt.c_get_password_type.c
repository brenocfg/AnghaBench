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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  PasswordType ;

/* Variables and functions */
 int /*<<< orphan*/  MD5_PASSWD_CHARSET ; 
 int MD5_PASSWD_LEN ; 
 int /*<<< orphan*/  PASSWORD_TYPE_MD5 ; 
 int /*<<< orphan*/  PASSWORD_TYPE_PLAINTEXT ; 
 int /*<<< orphan*/  PASSWORD_TYPE_SCRAM_SHA_256 ; 
 int SCRAM_KEY_LEN ; 
 scalar_t__ parse_scram_secret (char const*,int*,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int strspn (char const*,int /*<<< orphan*/ ) ; 

PasswordType
get_password_type(const char *shadow_pass)
{
	char	   *encoded_salt;
	int			iterations;
	uint8		stored_key[SCRAM_KEY_LEN];
	uint8		server_key[SCRAM_KEY_LEN];

	if (strncmp(shadow_pass, "md5", 3) == 0 &&
		strlen(shadow_pass) == MD5_PASSWD_LEN &&
		strspn(shadow_pass + 3, MD5_PASSWD_CHARSET) == MD5_PASSWD_LEN - 3)
		return PASSWORD_TYPE_MD5;
	if (parse_scram_secret(shadow_pass, &iterations, &encoded_salt,
							 stored_key, server_key))
		return PASSWORD_TYPE_SCRAM_SHA_256;
	return PASSWORD_TYPE_PLAINTEXT;
}