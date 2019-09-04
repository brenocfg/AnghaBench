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
struct hashtab {int size; } ;

/* Variables and functions */
 unsigned int strlen (char const*) ; 

__attribute__((used)) static unsigned int symhash(struct hashtab *h, const void *key)
{
	const char *p, *keyp;
	unsigned int size;
	unsigned int val;

	val = 0;
	keyp = key;
	size = strlen(keyp);
	for (p = keyp; (p - keyp) < size; p++)
		val = (val << 4 | (val >> (8*sizeof(unsigned int)-4))) ^ (*p);
	return val & (h->size - 1);
}