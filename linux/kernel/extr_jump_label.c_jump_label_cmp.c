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
struct jump_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ jump_entry_code (struct jump_entry const*) ; 
 scalar_t__ jump_entry_key (struct jump_entry const*) ; 

__attribute__((used)) static int jump_label_cmp(const void *a, const void *b)
{
	const struct jump_entry *jea = a;
	const struct jump_entry *jeb = b;

	/*
	 * Entrires are sorted by key.
	 */
	if (jump_entry_key(jea) < jump_entry_key(jeb))
		return -1;

	if (jump_entry_key(jea) > jump_entry_key(jeb))
		return 1;

	/*
	 * In the batching mode, entries should also be sorted by the code
	 * inside the already sorted list of entries, enabling a bsearch in
	 * the vector.
	 */
	if (jump_entry_code(jea) < jump_entry_code(jeb))
		return -1;

	if (jump_entry_code(jea) > jump_entry_code(jeb))
		return 1;

	return 0;
}