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
typedef  scalar_t__ u16 ;
struct es1968 {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDR1_CRAM_POINTER ; 
 scalar_t__ __maestro_read (struct es1968*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __maestro_write (struct es1968*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void apu_index_set(struct es1968 *chip, u16 index)
{
	int i;
	__maestro_write(chip, IDR1_CRAM_POINTER, index);
	for (i = 0; i < 1000; i++)
		if (__maestro_read(chip, IDR1_CRAM_POINTER) == index)
			return;
	dev_dbg(chip->card->dev, "APU register select failed. (Timeout)\n");
}