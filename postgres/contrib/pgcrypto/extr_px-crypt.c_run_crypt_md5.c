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
 char* px_crypt_md5 (char const*,char const*,char*,unsigned int) ; 

__attribute__((used)) static char *
run_crypt_md5(const char *psw, const char *salt,
			  char *buf, unsigned len)
{
	char	   *res;

	res = px_crypt_md5(psw, salt, buf, len);
	return res;
}