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
 scalar_t__ MD5_PASSWD_LEN ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  pg_md5_encrypt (char const*,char const*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

char *
PQencryptPassword(const char *passwd, const char *user)
{
	char	   *crypt_pwd;

	crypt_pwd = malloc(MD5_PASSWD_LEN + 1);
	if (!crypt_pwd)
		return NULL;

	if (!pg_md5_encrypt(passwd, user, strlen(user), crypt_pwd))
	{
		free(crypt_pwd);
		return NULL;
	}

	return crypt_pwd;
}