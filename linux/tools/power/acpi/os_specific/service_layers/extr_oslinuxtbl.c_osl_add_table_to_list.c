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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct osl_table_info {scalar_t__ instance; struct osl_table_info* next; int /*<<< orphan*/  signature; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_COMPARE_NAMESEG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ACPI_COPY_NAMESEG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 struct osl_table_info* calloc (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gbl_table_count ; 
 struct osl_table_info* gbl_table_list_head ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static acpi_status osl_add_table_to_list(char *signature, u32 instance)
{
	struct osl_table_info *new_info;
	struct osl_table_info *next;
	u32 next_instance = 0;
	u8 found = FALSE;

	new_info = calloc(1, sizeof(struct osl_table_info));
	if (!new_info) {
		return (AE_NO_MEMORY);
	}

	ACPI_COPY_NAMESEG(new_info->signature, signature);

	if (!gbl_table_list_head) {
		gbl_table_list_head = new_info;
	} else {
		next = gbl_table_list_head;
		while (1) {
			if (ACPI_COMPARE_NAMESEG(next->signature, signature)) {
				if (next->instance == instance) {
					found = TRUE;
				}
				if (next->instance >= next_instance) {
					next_instance = next->instance + 1;
				}
			}

			if (!next->next) {
				break;
			}
			next = next->next;
		}
		next->next = new_info;
	}

	if (found) {
		if (instance) {
			fprintf(stderr,
				"%4.4s: Warning unmatched table instance %d, expected %d\n",
				signature, instance, next_instance);
		}
		instance = next_instance;
	}

	new_info->instance = instance;
	gbl_table_count++;

	return (AE_OK);
}