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
struct px_crypt_algo {char* (* crypt ) (char const*,char const*,char*,unsigned int) ;int /*<<< orphan*/  id_len; scalar_t__ id; } ;

/* Variables and functions */
 struct px_crypt_algo* px_crypt_list ; 
 scalar_t__ strncmp (char const*,scalar_t__,int /*<<< orphan*/ ) ; 
 char* stub1 (char const*,char const*,char*,unsigned int) ; 

char *
px_crypt(const char *psw, const char *salt, char *buf, unsigned len)
{
	const struct px_crypt_algo *c;

	for (c = px_crypt_list; c->id; c++)
	{
		if (!c->id_len)
			break;
		if (strncmp(salt, c->id, c->id_len) == 0)
			break;
	}

	if (c->crypt == NULL)
		return NULL;

	return c->crypt(psw, salt, buf, len);
}