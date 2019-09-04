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
struct hdac_device {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 unsigned int AC_DEV_LIST_LEN_MASK ; 
 int /*<<< orphan*/  AC_PAR_DEVLIST_LEN ; 
 unsigned int AC_WCAP_DIGITAL ; 
 unsigned int AC_WID_PIN ; 
 unsigned int get_wcaps (struct hdac_device*,int /*<<< orphan*/ ) ; 
 unsigned int get_wcaps_type (unsigned int) ; 
 unsigned int snd_hdac_read_parm_uncached (struct hdac_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdac_hdmi_get_port_len(struct hdac_device *hdev, hda_nid_t nid)
{
	unsigned int caps;
	unsigned int type, param;

	caps = get_wcaps(hdev, nid);
	type = get_wcaps_type(caps);

	if (!(caps & AC_WCAP_DIGITAL) || (type != AC_WID_PIN))
		return 0;

	param = snd_hdac_read_parm_uncached(hdev, nid, AC_PAR_DEVLIST_LEN);
	if (param == -1)
		return param;

	return param & AC_DEV_LIST_LEN_MASK;
}