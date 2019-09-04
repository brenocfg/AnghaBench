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
 unsigned long partial_name_hash (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned int strlen (char const*) ; 

__attribute__((used)) static inline unsigned int
name_hash(const unsigned char *name)
{
	unsigned long hash = 0;
	unsigned int len = strlen((const char *)name);
	while (len--)
		hash = partial_name_hash(*name++, hash);
	return (unsigned int)hash;
}