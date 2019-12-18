#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int const) ; 
 TYPE_1__* tomoyo_current_namespace () ; 

__attribute__((used)) static bool tomoyo_namespace_jump(const char *domainname)
{
	const char *namespace = tomoyo_current_namespace()->name;
	const int len = strlen(namespace);

	return strncmp(domainname, namespace, len) ||
		(domainname[len] && domainname[len] != ' ');
}