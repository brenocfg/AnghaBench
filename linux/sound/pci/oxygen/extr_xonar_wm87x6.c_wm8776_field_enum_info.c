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
typedef  int u8 ;
struct snd_kcontrol {int private_value; } ;
struct snd_ctl_elem_info {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int LC_CONTROL_LIMITER ; 
#define  WM8776_ALCCTRL2 130 
#define  WM8776_ALCCTRL3 129 
#define  WM8776_LIMITER 128 
 int snd_ctl_enum_info (struct snd_ctl_elem_info*,int,int,char const* const*) ; 

__attribute__((used)) static int wm8776_field_enum_info(struct snd_kcontrol *ctl,
				  struct snd_ctl_elem_info *info)
{
	static const char *const hld[16] = {
		"0 ms", "2.67 ms", "5.33 ms", "10.6 ms",
		"21.3 ms", "42.7 ms", "85.3 ms", "171 ms",
		"341 ms", "683 ms", "1.37 s", "2.73 s",
		"5.46 s", "10.9 s", "21.8 s", "43.7 s",
	};
	static const char *const atk_lim[11] = {
		"0.25 ms", "0.5 ms", "1 ms", "2 ms",
		"4 ms", "8 ms", "16 ms", "32 ms",
		"64 ms", "128 ms", "256 ms",
	};
	static const char *const atk_alc[11] = {
		"8.40 ms", "16.8 ms", "33.6 ms", "67.2 ms",
		"134 ms", "269 ms", "538 ms", "1.08 s",
		"2.15 s", "4.3 s", "8.6 s",
	};
	static const char *const dcy_lim[11] = {
		"1.2 ms", "2.4 ms", "4.8 ms", "9.6 ms",
		"19.2 ms", "38.4 ms", "76.8 ms", "154 ms",
		"307 ms", "614 ms", "1.23 s",
	};
	static const char *const dcy_alc[11] = {
		"33.5 ms", "67.0 ms", "134 ms", "268 ms",
		"536 ms", "1.07 s", "2.14 s", "4.29 s",
		"8.58 s", "17.2 s", "34.3 s",
	};
	static const char *const tranwin[8] = {
		"0 us", "62.5 us", "125 us", "250 us",
		"500 us", "1 ms", "2 ms", "4 ms",
	};
	u8 max;
	const char *const *names;

	max = (ctl->private_value >> 12) & 0xf;
	switch ((ctl->private_value >> 24) & 0x1f) {
	case WM8776_ALCCTRL2:
		names = hld;
		break;
	case WM8776_ALCCTRL3:
		if (((ctl->private_value >> 20) & 0xf) == 0) {
			if (ctl->private_value & LC_CONTROL_LIMITER)
				names = atk_lim;
			else
				names = atk_alc;
		} else {
			if (ctl->private_value & LC_CONTROL_LIMITER)
				names = dcy_lim;
			else
				names = dcy_alc;
		}
		break;
	case WM8776_LIMITER:
		names = tranwin;
		break;
	default:
		return -ENXIO;
	}
	return snd_ctl_enum_info(info, 1, max + 1, names);
}