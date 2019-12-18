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
 char* downcase_identifier (char const*,int,int,int) ; 

char *
downcase_truncate_identifier(const char *ident, int len, bool warn)
{
	return downcase_identifier(ident, len, warn, true);
}