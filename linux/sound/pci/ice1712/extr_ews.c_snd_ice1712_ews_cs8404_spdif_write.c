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
struct TYPE_2__ {int subvendor; } ;
struct snd_ice1712 {int /*<<< orphan*/  i2c; TYPE_1__ eeprom; struct ews_spec* spec; } ;
struct ews_spec {int /*<<< orphan*/ * i2cdevs; } ;

/* Variables and functions */
 size_t EWS_I2C_88D ; 
 size_t EWS_I2C_CS8404 ; 
#define  ICE1712_SUBDEVICE_EWS88D 132 
#define  ICE1712_SUBDEVICE_EWS88MT 131 
#define  ICE1712_SUBDEVICE_EWS88MT_NEW 130 
#define  ICE1712_SUBDEVICE_PHASE88 129 
#define  ICE1712_SUBDEVICE_TS88 128 
 int /*<<< orphan*/  snd_i2c_lock (int /*<<< orphan*/ ) ; 
 int snd_i2c_readbytes (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int snd_i2c_sendbytes (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  snd_i2c_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_ice1712_ews_cs8404_spdif_write(struct snd_ice1712 *ice, unsigned char bits)
{
	struct ews_spec *spec = ice->spec;
	unsigned char bytes[2];

	snd_i2c_lock(ice->i2c);
	switch (ice->eeprom.subvendor) {
	case ICE1712_SUBDEVICE_EWS88MT:
	case ICE1712_SUBDEVICE_EWS88MT_NEW:
	case ICE1712_SUBDEVICE_PHASE88:
	case ICE1712_SUBDEVICE_TS88:
		if (snd_i2c_sendbytes(spec->i2cdevs[EWS_I2C_CS8404], &bits, 1)
		    != 1)
			goto _error;
		break;
	case ICE1712_SUBDEVICE_EWS88D:
		if (snd_i2c_readbytes(spec->i2cdevs[EWS_I2C_88D], bytes, 2)
		    != 2)
			goto _error;
		if (bits != bytes[1]) {
			bytes[1] = bits;
			if (snd_i2c_sendbytes(spec->i2cdevs[EWS_I2C_88D],
					      bytes, 2) != 2)
				goto _error;
		}
		break;
	}
 _error:
	snd_i2c_unlock(ice->i2c);
}