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
struct hdac_device {int /*<<< orphan*/  vendor_verbs; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned int* snd_array_new (int /*<<< orphan*/ *) ; 

int snd_hdac_regmap_add_vendor_verb(struct hdac_device *codec,
				    unsigned int verb)
{
	unsigned int *p = snd_array_new(&codec->vendor_verbs);

	if (!p)
		return -ENOMEM;
	*p = verb | 0x800; /* set GET bit */
	return 0;
}