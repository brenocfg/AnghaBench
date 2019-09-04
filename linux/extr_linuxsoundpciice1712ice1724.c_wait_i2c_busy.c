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
struct snd_ice1712 {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_CTRL ; 
 int /*<<< orphan*/  ICEREG1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int VT1724_I2C_BUSY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wait_i2c_busy(struct snd_ice1712 *ice)
{
	int t = 0x10000;
	while ((inb(ICEREG1724(ice, I2C_CTRL)) & VT1724_I2C_BUSY) && t--)
		;
	if (t == -1)
		dev_err(ice->card->dev, "i2c busy timeout\n");
}