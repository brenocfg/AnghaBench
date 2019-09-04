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
 int /*<<< orphan*/  define_config (char const*,int,unsigned int) ; 
 scalar_t__ is_defined_config (char const*,int,unsigned int) ; 
 int /*<<< orphan*/  print_dep (char const*,int,char*) ; 
 unsigned int strhash (char const*,int) ; 

__attribute__((used)) static void use_config(const char *m, int slen)
{
	unsigned int hash = strhash(m, slen);

	if (is_defined_config(m, slen, hash))
	    return;

	define_config(m, slen, hash);
	print_dep(m, slen, "include/config");
}