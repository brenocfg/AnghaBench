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
struct snd_kcontrol {int dummy; } ;
struct snd_ctl_elem_info {int dummy; } ;

/* Variables and functions */
 int snd_ctl_enum_info (struct snd_ctl_elem_info*,int,int,char const* const*) ; 

__attribute__((used)) static int snd_vt1724_pro_route_info(struct snd_kcontrol *kcontrol,
				     struct snd_ctl_elem_info *uinfo)
{
	static const char * const texts[] = {
		"PCM Out", /* 0 */
		"H/W In 0", "H/W In 1", /* 1-2 */
		"IEC958 In L", "IEC958 In R", /* 3-4 */
	};

	return snd_ctl_enum_info(uinfo, 1, 5, texts);
}