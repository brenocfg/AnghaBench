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
 scalar_t__ memcmp (char const*,char const*,unsigned int) ; 
 unsigned int strlen (char const*) ; 

__attribute__((used)) static bool sym_is(const char *name, unsigned namelen, const char *symbol)
{
	if (namelen != strlen(symbol))
		return false;

	return memcmp(name, symbol, namelen) == 0;
}