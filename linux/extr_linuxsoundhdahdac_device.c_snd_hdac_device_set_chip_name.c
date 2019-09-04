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
struct hdac_device {char* chip_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 

int snd_hdac_device_set_chip_name(struct hdac_device *codec, const char *name)
{
	char *newname;

	if (!name)
		return 0;
	newname = kstrdup(name, GFP_KERNEL);
	if (!newname)
		return -ENOMEM;
	kfree(codec->chip_name);
	codec->chip_name = newname;
	return 0;
}