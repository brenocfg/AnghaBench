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
struct snd_ice1712 {int dummy; } ;

/* Variables and functions */
#define  AK4396_CTRL1 132 
#define  AK4396_CTRL2 131 
#define  AK4396_CTRL3 130 
#define  AK4396_LCH_ATT 129 
#define  AK4396_RCH_ATT 128 
 unsigned int ARRAY_SIZE (unsigned short*) ; 
 int /*<<< orphan*/  ak4396_write (struct snd_ice1712*,int const,unsigned short) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void ak4396_init(struct snd_ice1712 *ice)
{
	static unsigned short ak4396_inits[] = {
		AK4396_CTRL1,	   0x87,   /* I2S Normal Mode, 24 bit */
		AK4396_CTRL2,	   0x02,
		AK4396_CTRL3,	   0x00, 
		AK4396_LCH_ATT,	 0x00,
		AK4396_RCH_ATT,	 0x00,
	};

	unsigned int i;

	/* initialize ak4396 codec */
	/* reset codec */
	ak4396_write(ice, AK4396_CTRL1, 0x86);
	msleep(100);
	ak4396_write(ice, AK4396_CTRL1, 0x87);

	for (i = 0; i < ARRAY_SIZE(ak4396_inits); i += 2)
		ak4396_write(ice, ak4396_inits[i], ak4396_inits[i+1]);
}