#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_wss {int hardware; TYPE_1__* card; } ;
struct TYPE_2__ {char const* shortname; } ;

/* Variables and functions */
#define  WSS_HW_AD1845 145 
#define  WSS_HW_AD1847 144 
#define  WSS_HW_AD1848 143 
#define  WSS_HW_CMI8330 142 
#define  WSS_HW_CS4231 141 
#define  WSS_HW_CS4231A 140 
#define  WSS_HW_CS4232 139 
#define  WSS_HW_CS4232A 138 
#define  WSS_HW_CS4235 137 
#define  WSS_HW_CS4236 136 
#define  WSS_HW_CS4236B 135 
#define  WSS_HW_CS4237B 134 
#define  WSS_HW_CS4238B 133 
#define  WSS_HW_CS4239 132 
#define  WSS_HW_CS4248 131 
#define  WSS_HW_INTERWAVE 130 
#define  WSS_HW_OPL3SA2 129 
#define  WSS_HW_OPTI93X 128 

const char *snd_wss_chip_id(struct snd_wss *chip)
{
	switch (chip->hardware) {
	case WSS_HW_CS4231:
		return "CS4231";
	case WSS_HW_CS4231A:
		return "CS4231A";
	case WSS_HW_CS4232:
		return "CS4232";
	case WSS_HW_CS4232A:
		return "CS4232A";
	case WSS_HW_CS4235:
		return "CS4235";
	case WSS_HW_CS4236:
		return "CS4236";
	case WSS_HW_CS4236B:
		return "CS4236B";
	case WSS_HW_CS4237B:
		return "CS4237B";
	case WSS_HW_CS4238B:
		return "CS4238B";
	case WSS_HW_CS4239:
		return "CS4239";
	case WSS_HW_INTERWAVE:
		return "AMD InterWave";
	case WSS_HW_OPL3SA2:
		return chip->card->shortname;
	case WSS_HW_AD1845:
		return "AD1845";
	case WSS_HW_OPTI93X:
		return "OPTi 93x";
	case WSS_HW_AD1847:
		return "AD1847";
	case WSS_HW_AD1848:
		return "AD1848";
	case WSS_HW_CS4248:
		return "CS4248";
	case WSS_HW_CMI8330:
		return "CMI8330/C3D";
	default:
		return "???";
	}
}