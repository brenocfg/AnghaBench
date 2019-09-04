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
struct hdac_device {scalar_t__ afg; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_PAR_POWER_STATE ; 
 int AC_WCAP_POWER ; 
 int get_wcaps (struct hdac_device*,scalar_t__) ; 
 int snd_hdac_read_parm (struct hdac_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t power_caps_show(struct hdac_device *codec, hda_nid_t nid,
			       struct widget_attribute *attr, char *buf)
{
	if (nid != codec->afg && !(get_wcaps(codec, nid) & AC_WCAP_POWER))
		return 0;
	return sprintf(buf, "0x%08x\n",
		       snd_hdac_read_parm(codec, nid, AC_PAR_POWER_STATE));
}