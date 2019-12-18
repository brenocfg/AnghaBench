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
struct display_info {int mode; int /*<<< orphan*/  default_val; } ;

/* Variables and functions */
#define  MODE_LIST_PROPS 129 
#define  MODE_LIST_SUBNODES 128 
 int /*<<< orphan*/  assert (char const*) ; 
 void* fdt_getprop (void const*,int,char const*,int*) ; 
 int list_properties (void const*,int) ; 
 int list_subnodes (void const*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report_error (char const*,int) ; 
 int /*<<< orphan*/  show_data (struct display_info*,void const*,int) ; 

__attribute__((used)) static int show_data_for_item(const void *blob, struct display_info *disp,
		int node, const char *property)
{
	const void *value = NULL;
	int len, err = 0;

	switch (disp->mode) {
	case MODE_LIST_PROPS:
		err = list_properties(blob, node);
		break;

	case MODE_LIST_SUBNODES:
		err = list_subnodes(blob, node);
		break;

	default:
		assert(property);
		value = fdt_getprop(blob, node, property, &len);
		if (value) {
			if (show_data(disp, value, len))
				err = -1;
			else
				printf("\n");
		} else if (disp->default_val) {
			puts(disp->default_val);
		} else {
			report_error(property, len);
			err = -1;
		}
		break;
	}

	return err;
}