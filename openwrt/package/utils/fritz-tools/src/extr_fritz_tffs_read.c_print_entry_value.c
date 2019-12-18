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
struct tffs_entry {int* val; int /*<<< orphan*/  header; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int get_header_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void print_entry_value(const struct tffs_entry *entry)
{
	int i;

	/* These are NOT NULL terminated. */
	for (i = 0; i < get_header_len(entry->header); i++)
		fprintf(stdout, "%c", entry->val[i]);
}