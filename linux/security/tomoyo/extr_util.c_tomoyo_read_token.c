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
struct tomoyo_acl_param {char* data; } ;

/* Variables and functions */
 char* strchr (char*,char) ; 
 int strlen (char*) ; 

char *tomoyo_read_token(struct tomoyo_acl_param *param)
{
	char *pos = param->data;
	char *del = strchr(pos, ' ');

	if (del)
		*del++ = '\0';
	else
		del = pos + strlen(pos);
	param->data = del;
	return pos;
}