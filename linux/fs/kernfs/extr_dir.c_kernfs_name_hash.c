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
 unsigned long INT_MAX ; 
 unsigned long end_name_hash (unsigned long) ; 
 unsigned long init_name_hash (void const*) ; 
 unsigned long partial_name_hash (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned int strlen (char const*) ; 

__attribute__((used)) static unsigned int kernfs_name_hash(const char *name, const void *ns)
{
	unsigned long hash = init_name_hash(ns);
	unsigned int len = strlen(name);
	while (len--)
		hash = partial_name_hash(*name++, hash);
	hash = end_name_hash(hash);
	hash &= 0x7fffffffU;
	/* Reserve hash numbers 0, 1 and INT_MAX for magic directory entries */
	if (hash < 2)
		hash += 2;
	if (hash >= INT_MAX)
		hash = INT_MAX - 1;
	return hash;
}