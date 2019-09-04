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
typedef  enum fpm_address_domain { ____Placeholder_fpm_address_domain } fpm_address_domain ;

/* Variables and functions */
 int FPM_AF_INET ; 
 int FPM_AF_UNIX ; 
 scalar_t__ strchr (char*,char) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strspn (char*,char*) ; 

enum fpm_address_domain fpm_sockets_domain_from_address(char *address) /* {{{ */
{
	if (strchr(address, ':')) {
		return FPM_AF_INET;
	}

	if (strlen(address) == strspn(address, "0123456789")) {
		return FPM_AF_INET;
	}
	return FPM_AF_UNIX;
}