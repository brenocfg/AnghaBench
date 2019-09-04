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
 int USBG_NAMELEN ; 
 unsigned int strlen (char const*) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static const char *usbg_check_wwn(const char *name)
{
	const char *n;
	unsigned int len;

	n = strstr(name, "naa.");
	if (!n)
		return NULL;
	n += 4;
	len = strlen(n);
	if (len == 0 || len > USBG_NAMELEN - 1)
		return NULL;
	return n;
}