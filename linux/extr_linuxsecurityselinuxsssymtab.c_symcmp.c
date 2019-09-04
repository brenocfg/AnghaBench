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
struct hashtab {int dummy; } ;

/* Variables and functions */
 int strcmp (char const*,char const*) ; 

__attribute__((used)) static int symcmp(struct hashtab *h, const void *key1, const void *key2)
{
	const char *keyp1, *keyp2;

	keyp1 = key1;
	keyp2 = key2;
	return strcmp(keyp1, keyp2);
}