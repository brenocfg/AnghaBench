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
struct nm256 {int buffer_size; scalar_t__ buffer; TYPE_1__* card; scalar_t__ buffer_start; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  memcpy_toio (scalar_t__,void*,int) ; 

__attribute__((used)) static inline void
snd_nm256_write_buffer(struct nm256 *chip, void *src, int offset, int size)
{
	offset -= chip->buffer_start;
#ifdef CONFIG_SND_DEBUG
	if (offset < 0 || offset >= chip->buffer_size) {
		dev_err(chip->card->dev,
			"write_buffer invalid offset = %d size = %d\n",
			   offset, size);
		return;
	}
#endif
	memcpy_toio(chip->buffer + offset, src, size);
}