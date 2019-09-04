#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct au1100fb_device {int panel_idx; TYPE_1__* panel; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENODEV ; 
 scalar_t__ fb_get_options (int /*<<< orphan*/ ,char**) ; 
 TYPE_1__* known_lcd_panels ; 
 int /*<<< orphan*/  print_err (char*) ; 
 int /*<<< orphan*/  print_info (char*,char*) ; 
 int /*<<< orphan*/  print_warn (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int au1100fb_setup(struct au1100fb_device *fbdev)
{
	char *this_opt, *options;
	int num_panels = ARRAY_SIZE(known_lcd_panels);

	if (num_panels <= 0) {
		print_err("No LCD panels supported by driver!");
		return -ENODEV;
	}

	if (fb_get_options(DRIVER_NAME, &options))
		return -ENODEV;
	if (!options)
		return -ENODEV;

	while ((this_opt = strsep(&options, ",")) != NULL) {
		/* Panel option */
		if (!strncmp(this_opt, "panel:", 6)) {
			int i;
			this_opt += 6;
			for (i = 0; i < num_panels; i++) {
				if (!strncmp(this_opt, known_lcd_panels[i].name,
					     strlen(this_opt))) {
					fbdev->panel = &known_lcd_panels[i];
					fbdev->panel_idx = i;
					break;
				}
			}
			if (i >= num_panels) {
				print_warn("Panel '%s' not supported!", this_opt);
				return -ENODEV;
			}
		}
		/* Unsupported option */
		else
			print_warn("Unsupported option \"%s\"", this_opt);
	}

	print_info("Panel=%s", fbdev->panel->name);

	return 0;
}