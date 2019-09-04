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
struct omapfb2_device {int num_displays; TYPE_2__* displays; } ;
struct omap_dss_device {TYPE_1__* dev; scalar_t__ alias; scalar_t__ name; } ;
struct TYPE_4__ {struct omap_dss_device* dssdev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * of_node; } ;

/* Variables and functions */
 int of_alias_get_id (int /*<<< orphan*/ *,char*) ; 
 char* omapdss_get_default_display_name () ; 
 scalar_t__ strcmp (char const*,scalar_t__) ; 

__attribute__((used)) static struct omap_dss_device *
omapfb_find_default_display(struct omapfb2_device *fbdev)
{
	const char *def_name;
	int i;

	/*
	 * Search with the display name from the user or the board file,
	 * comparing to display names and aliases
	 */

	def_name = omapdss_get_default_display_name();

	if (def_name) {
		for (i = 0; i < fbdev->num_displays; ++i) {
			struct omap_dss_device *dssdev;

			dssdev = fbdev->displays[i].dssdev;

			if (dssdev->name && strcmp(def_name, dssdev->name) == 0)
				return dssdev;

			if (strcmp(def_name, dssdev->alias) == 0)
				return dssdev;
		}

		/* def_name given but not found */
		return NULL;
	}

	/* then look for DT alias display0 */
	for (i = 0; i < fbdev->num_displays; ++i) {
		struct omap_dss_device *dssdev;
		int id;

		dssdev = fbdev->displays[i].dssdev;

		if (dssdev->dev->of_node == NULL)
			continue;

		id = of_alias_get_id(dssdev->dev->of_node, "display");
		if (id == 0)
			return dssdev;
	}

	/* return the first display we have in the list */
	return fbdev->displays[0].dssdev;
}