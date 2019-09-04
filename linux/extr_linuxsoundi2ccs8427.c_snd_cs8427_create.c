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
struct snd_i2c_device {int /*<<< orphan*/  private_free; struct cs8427* private_data; } ;
struct snd_i2c_bus {int dummy; } ;
struct cs8427 {unsigned int reset_timeout; } ;

/* Variables and functions */
 unsigned char CS8427_ADDR ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct cs8427* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cs8427_free ; 
 int snd_cs8427_init (struct snd_i2c_bus*,struct snd_i2c_device*) ; 
 int snd_i2c_device_create (struct snd_i2c_bus*,char*,unsigned char,struct snd_i2c_device**) ; 
 int /*<<< orphan*/  snd_i2c_device_free (struct snd_i2c_device*) ; 

int snd_cs8427_create(struct snd_i2c_bus *bus,
		      unsigned char addr,
		      unsigned int reset_timeout,
		      struct snd_i2c_device **r_cs8427)
{
	int err;
	struct cs8427 *chip;
	struct snd_i2c_device *device;

	err = snd_i2c_device_create(bus, "CS8427", CS8427_ADDR | (addr & 7),
				    &device);
	if (err < 0)
		return err;
	chip = device->private_data = kzalloc(sizeof(*chip), GFP_KERNEL);
	if (chip == NULL) {
		snd_i2c_device_free(device);
		return -ENOMEM;
	}
	device->private_free = snd_cs8427_free;

	if (reset_timeout < 1)
		reset_timeout = 1;
	chip->reset_timeout = reset_timeout;

	err = snd_cs8427_init(bus, device);
	if (err)
		goto __fail;

#if 0	// it's nice for read tests
	{
	char buf[128];
	int xx;
	buf[0] = 0x81;
	snd_i2c_sendbytes(device, buf, 1);
	snd_i2c_readbytes(device, buf, 127);
	for (xx = 0; xx < 127; xx++)
		printk(KERN_DEBUG "reg[0x%x] = 0x%x\n", xx+1, buf[xx]);
	}
#endif
	
	if (r_cs8427)
		*r_cs8427 = device;
	return 0;

      __fail:
      	snd_i2c_device_free(device);
      	return err < 0 ? err : -EIO;
}