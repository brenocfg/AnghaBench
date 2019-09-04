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
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 

__attribute__((used)) static inline int iioutils_check_suffix(const char *str, const char *suffix)
{
	return strlen(str) >= strlen(suffix) &&
		strncmp(str+strlen(str)-strlen(suffix),
			suffix, strlen(suffix)) == 0;
}