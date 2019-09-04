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
struct snd_opl4 {int /*<<< orphan*/  hardware; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  OPL3_HW_OPL4 ; 
 int /*<<< orphan*/  OPL3_HW_OPL4_ML ; 
 int OPL4_DEVICE_ID_MASK ; 
 int /*<<< orphan*/  OPL4_REG_MEMORY_CONFIGURATION ; 
 int /*<<< orphan*/  OPL4_REG_MIX_CONTROL_FM ; 
 int /*<<< orphan*/  OPL4_REG_MIX_CONTROL_PCM ; 
 int /*<<< orphan*/  snd_opl4_enable_opl4 (struct snd_opl4*) ; 
 int snd_opl4_read (struct snd_opl4*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_opl4_write (struct snd_opl4*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_printdd (char*,int,...) ; 

__attribute__((used)) static int snd_opl4_detect(struct snd_opl4 *opl4)
{
	u8 id1, id2;

	snd_opl4_enable_opl4(opl4);

	id1 = snd_opl4_read(opl4, OPL4_REG_MEMORY_CONFIGURATION);
	snd_printdd("OPL4[02]=%02x\n", id1);
	switch (id1 & OPL4_DEVICE_ID_MASK) {
	case 0x20:
		opl4->hardware = OPL3_HW_OPL4;
		break;
	case 0x40:
		opl4->hardware = OPL3_HW_OPL4_ML;
		break;
	default:
		return -ENODEV;
	}

	snd_opl4_write(opl4, OPL4_REG_MIX_CONTROL_FM, 0x00);
	snd_opl4_write(opl4, OPL4_REG_MIX_CONTROL_PCM, 0xff);
	id1 = snd_opl4_read(opl4, OPL4_REG_MIX_CONTROL_FM);
	id2 = snd_opl4_read(opl4, OPL4_REG_MIX_CONTROL_PCM);
	snd_printdd("OPL4 id1=%02x id2=%02x\n", id1, id2);
       	if (id1 != 0x00 || id2 != 0xff)
		return -ENODEV;

	snd_opl4_write(opl4, OPL4_REG_MIX_CONTROL_FM, 0x3f);
	snd_opl4_write(opl4, OPL4_REG_MIX_CONTROL_PCM, 0x3f);
	snd_opl4_write(opl4, OPL4_REG_MEMORY_CONFIGURATION, 0x00);
	return 0;
}