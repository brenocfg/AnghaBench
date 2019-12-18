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
 int /*<<< orphan*/ * o_meta ; 
 size_t o_msize ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int match_meta(const char * meta, size_t size)
{
	size_t i, j;
	int match;

	for (i = 0; i < o_msize; i++)
	{
		for (match = 0, j = 0; j < size; j += (strlen(&meta[j])+1))
			if (strcmp(&meta[j], o_meta[i])==0) { match++; break; }
		if (!match) return 0;
	}
	return 1;
}