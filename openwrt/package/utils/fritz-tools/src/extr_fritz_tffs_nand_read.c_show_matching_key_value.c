#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct tffs_key_name_table {size_t size; TYPE_1__* entries; } ;
struct tffs_entry {int /*<<< orphan*/  val; } ;
struct TYPE_2__ {char* val; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 scalar_t__ find_entry (int /*<<< orphan*/ ,struct tffs_entry*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 char* name_filter ; 
 int /*<<< orphan*/  print_entry_value (struct tffs_entry*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int show_matching_key_value(struct tffs_key_name_table *key_names)
{
	struct tffs_entry tmp;
	const char *name;

	for (uint32_t i = 0; i < key_names->size; i++) {
		name = key_names->entries[i].val;

		if (strncmp(name, name_filter, strlen(name)) == 0) {
			if (find_entry(key_names->entries[i].id, &tmp)) {
				print_entry_value(&tmp);
				printf("\n");
				free(tmp.val);
				return EXIT_SUCCESS;
			} else {
				fprintf(stderr,
					"ERROR: no value found for name %s!\n",
					name);
				return EXIT_FAILURE;
			}
		}
	}

	fprintf(stderr, "ERROR: Unknown key name %s!\n", name_filter);
	return EXIT_FAILURE;
}