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
struct widget_attribute {int dummy; } ;
struct hdac_device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_GET_CONFIG_DEFAULT ; 
 scalar_t__ AC_WID_PIN ; 
 int /*<<< orphan*/  get_wcaps (struct hdac_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_wcaps_type (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_hdac_read (struct hdac_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static ssize_t pin_cfg_show(struct hdac_device *codec, hda_nid_t nid,
			    struct widget_attribute *attr, char *buf)
{
	unsigned int val;

	if (get_wcaps_type(get_wcaps(codec, nid)) != AC_WID_PIN)
		return 0;
	if (snd_hdac_read(codec, nid, AC_VERB_GET_CONFIG_DEFAULT, 0, &val))
		return 0;
	return sprintf(buf, "0x%08x\n", val);
}