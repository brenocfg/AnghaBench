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
 char* px_crypt_des (char const*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 unsigned int strlen (char*) ; 

__attribute__((used)) static char *
run_crypt_des(const char *psw, const char *salt,
			  char *buf, unsigned len)
{
	char	   *res;

	res = px_crypt_des(psw, salt);
	if (res == NULL || strlen(res) > len - 1)
		return NULL;
	strcpy(buf, res);
	return buf;
}