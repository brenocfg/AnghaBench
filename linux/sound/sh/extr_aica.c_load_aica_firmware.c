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
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 TYPE_1__* pd ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spu_disable () ; 
 int /*<<< orphan*/  spu_enable () ; 
 int /*<<< orphan*/  spu_memload (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spu_reset () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int load_aica_firmware(void)
{
	int err;
	const struct firmware *fw_entry;
	spu_reset();
	err = request_firmware(&fw_entry, "aica_firmware.bin", &pd->dev);
	if (unlikely(err))
		return err;
	/* write firmware into memory */
	spu_disable();
	spu_memload(0, fw_entry->data, fw_entry->size);
	spu_enable();
	release_firmware(fw_entry);
	return err;
}