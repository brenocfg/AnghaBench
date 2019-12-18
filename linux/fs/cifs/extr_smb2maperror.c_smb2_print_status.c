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
typedef  scalar_t__ __le32 ;
struct TYPE_2__ {scalar_t__ smb2_status; int /*<<< orphan*/ * status_string; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_notice (char*,scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_1__* smb2_error_map_table ; 

__attribute__((used)) static void
smb2_print_status(__le32 status)
{
	int idx = 0;

	while (smb2_error_map_table[idx].status_string != NULL) {
		if ((smb2_error_map_table[idx].smb2_status) == status) {
			pr_notice("Status code returned 0x%08x %s\n", status,
				  smb2_error_map_table[idx].status_string);
		}
		idx++;
	}
	return;
}