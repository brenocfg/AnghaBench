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
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 

__attribute__((used)) static inline int match_prefix(char *prefix, int plen, char *option, int olen)
{
	if (plen > olen)
		return 0;

	return !memcmp(prefix, option, plen);
}