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
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int pg_md5_hash (char*,size_t,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char const*) ; 

bool
pg_md5_encrypt(const char *passwd, const char *salt, size_t salt_len,
			   char *buf)
{
	size_t		passwd_len = strlen(passwd);

	/* +1 here is just to avoid risk of unportable malloc(0) */
	char	   *crypt_buf = malloc(passwd_len + salt_len + 1);
	bool		ret;

	if (!crypt_buf)
		return false;

	/*
	 * Place salt at the end because it may be known by users trying to crack
	 * the MD5 output.
	 */
	memcpy(crypt_buf, passwd, passwd_len);
	memcpy(crypt_buf + passwd_len, salt, salt_len);

	strcpy(buf, "md5");
	ret = pg_md5_hash(crypt_buf, passwd_len + salt_len, buf + 3);

	free(crypt_buf);

	return ret;
}