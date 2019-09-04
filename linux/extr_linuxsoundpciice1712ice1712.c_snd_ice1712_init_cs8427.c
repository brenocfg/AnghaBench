#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  setup_rate; int /*<<< orphan*/  close; int /*<<< orphan*/  open; } ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct snd_ice1712 {int cs8427_timeout; TYPE_3__ spdif; TYPE_1__* card; int /*<<< orphan*/  cs8427; int /*<<< orphan*/  i2c; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  close_cs8427 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  open_cs8427 ; 
 int /*<<< orphan*/  setup_cs8427 ; 
 int snd_cs8427_create (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

int snd_ice1712_init_cs8427(struct snd_ice1712 *ice, int addr)
{
	int err;

	err = snd_cs8427_create(ice->i2c, addr,
		(ice->cs8427_timeout * HZ) / 1000, &ice->cs8427);
	if (err < 0) {
		dev_err(ice->card->dev, "CS8427 initialization failed\n");
		return err;
	}
	ice->spdif.ops.open = open_cs8427;
	ice->spdif.ops.close = close_cs8427;
	ice->spdif.ops.setup_rate = setup_cs8427;
	return 0;
}