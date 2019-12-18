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
 scalar_t__ strcmp (char const*,char*) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static int is_vmlinux(const char *modname)
{
	const char *myname;

	myname = strrchr(modname, '/');
	if (myname)
		myname++;
	else
		myname = modname;

	return (strcmp(myname, "vmlinux") == 0) ||
	       (strcmp(myname, "vmlinux.o") == 0);
}