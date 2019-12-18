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
struct snd_ice1712 {int /*<<< orphan*/  i2c; TYPE_1__* card; struct ews_spec* spec; } ;
struct ews_spec {int /*<<< orphan*/ * i2cdevs; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 size_t EWS_I2C_6FIRE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_i2c_lock (int /*<<< orphan*/ ) ; 
 int snd_i2c_readbytes (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int snd_i2c_sendbytes (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  snd_i2c_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_ice1712_6fire_read_pca(struct snd_ice1712 *ice, unsigned char reg)
{
	unsigned char byte;
	struct ews_spec *spec = ice->spec;

	snd_i2c_lock(ice->i2c);
	byte = reg;
	if (snd_i2c_sendbytes(spec->i2cdevs[EWS_I2C_6FIRE], &byte, 1) != 1) {
		snd_i2c_unlock(ice->i2c);
		dev_err(ice->card->dev, "cannot send pca\n");
		return -EIO;
	}

	byte = 0;
	if (snd_i2c_readbytes(spec->i2cdevs[EWS_I2C_6FIRE], &byte, 1) != 1) {
		snd_i2c_unlock(ice->i2c);
		dev_err(ice->card->dev, "cannot read pca\n");
		return -EIO;
	}
	snd_i2c_unlock(ice->i2c);
	return byte;
}