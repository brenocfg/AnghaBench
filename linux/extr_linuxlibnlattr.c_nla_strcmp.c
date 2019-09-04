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
struct nlattr {int dummy; } ;

/* Variables and functions */
 int memcmp (char*,char const*,int) ; 
 char* nla_data (struct nlattr const*) ; 
 int nla_len (struct nlattr const*) ; 
 int strlen (char const*) ; 

int nla_strcmp(const struct nlattr *nla, const char *str)
{
	int len = strlen(str);
	char *buf = nla_data(nla);
	int attrlen = nla_len(nla);
	int d;

	if (attrlen > 0 && buf[attrlen - 1] == '\0')
		attrlen--;

	d = attrlen - len;
	if (d == 0)
		d = memcmp(nla_data(nla), str, len);

	return d;
}