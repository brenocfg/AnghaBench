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
struct format_field {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int field_is_dynamic(struct format_field *field)
{
	if (strncmp(field->type, "__data_loc", 10) == 0)
		return 1;

	return 0;
}