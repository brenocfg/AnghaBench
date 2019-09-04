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
struct text_lookup {int dummy; } ;
typedef  struct text_lookup lookup_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct text_lookup*) ; 
 struct text_lookup* bzalloc (int) ; 
 int /*<<< orphan*/  text_lookup_add (struct text_lookup*,char const*) ; 

lookup_t *text_lookup_create(const char *path)
{
	struct text_lookup *lookup = bzalloc(sizeof(struct text_lookup));

	if (!text_lookup_add(lookup, path)) {
		bfree(lookup);
		lookup = NULL;
	}

	return lookup;
}