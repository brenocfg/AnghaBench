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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct tffs_key_name_table {int size; TYPE_1__* entries; } ;
struct tffs_entry {int dummy; } ;
struct TYPE_2__ {char* val; int /*<<< orphan*/ * id; } ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 scalar_t__ find_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct tffs_entry*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 char* name_filter ; 
 int /*<<< orphan*/  print_entry_value (struct tffs_entry*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_entry_header_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int show_matching_key_value(uint8_t *buffer,
				   struct tffs_key_name_table *key_names)
{
	int i;
	uint16_t id;
	struct tffs_entry tmp;
	const char *name;

	for (i = 0; i < key_names->size; i++) {
		name = key_names->entries[i].val;

		if (strncmp(name, name_filter, strlen(name)) == 0) {
			id = to_entry_header_id(*key_names->entries[i].id);

			if (find_entry(buffer, id, &tmp)) {
				print_entry_value(&tmp);
				printf("\n");
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