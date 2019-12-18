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
 scalar_t__ ap_get_server_banner () ; 
 scalar_t__ ap_get_server_version () ; 

__attribute__((used)) static char *php_apache_get_version()
{
#if MODULE_MAGIC_NUMBER_MAJOR >= 20060905
	return (char *) ap_get_server_banner();
#else
	return (char *) ap_get_server_version();
#endif
}