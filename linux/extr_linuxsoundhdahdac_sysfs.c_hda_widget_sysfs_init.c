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
struct hdac_device {scalar_t__ widgets; } ;

/* Variables and functions */
 int widget_tree_create (struct hdac_device*) ; 
 int /*<<< orphan*/  widget_tree_free (struct hdac_device*) ; 

int hda_widget_sysfs_init(struct hdac_device *codec)
{
	int err;

	if (codec->widgets)
		return 0; /* already created */

	err = widget_tree_create(codec);
	if (err < 0) {
		widget_tree_free(codec);
		return err;
	}

	return 0;
}