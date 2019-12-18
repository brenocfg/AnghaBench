#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct tomoyo_number_union {unsigned long* values; int* value_type; TYPE_2__* group; } ;
struct tomoyo_io_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_4__ {TYPE_1__* group_name; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
#define  TOMOYO_VALUE_TYPE_HEXADECIMAL 129 
#define  TOMOYO_VALUE_TYPE_OCTAL 128 
 int /*<<< orphan*/  tomoyo_addprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  tomoyo_io_printf (struct tomoyo_io_buffer*,char*,char*) ; 
 int /*<<< orphan*/  tomoyo_set_string (struct tomoyo_io_buffer*,char*) ; 

__attribute__((used)) static void tomoyo_print_number_union_nospace
(struct tomoyo_io_buffer *head, const struct tomoyo_number_union *ptr)
{
	if (ptr->group) {
		tomoyo_set_string(head, "@");
		tomoyo_set_string(head, ptr->group->group_name->name);
	} else {
		int i;
		unsigned long min = ptr->values[0];
		const unsigned long max = ptr->values[1];
		u8 min_type = ptr->value_type[0];
		const u8 max_type = ptr->value_type[1];
		char buffer[128];

		buffer[0] = '\0';
		for (i = 0; i < 2; i++) {
			switch (min_type) {
			case TOMOYO_VALUE_TYPE_HEXADECIMAL:
				tomoyo_addprintf(buffer, sizeof(buffer),
						 "0x%lX", min);
				break;
			case TOMOYO_VALUE_TYPE_OCTAL:
				tomoyo_addprintf(buffer, sizeof(buffer),
						 "0%lo", min);
				break;
			default:
				tomoyo_addprintf(buffer, sizeof(buffer), "%lu",
						 min);
				break;
			}
			if (min == max && min_type == max_type)
				break;
			tomoyo_addprintf(buffer, sizeof(buffer), "-");
			min_type = max_type;
			min = max;
		}
		tomoyo_io_printf(head, "%s", buffer);
	}
}