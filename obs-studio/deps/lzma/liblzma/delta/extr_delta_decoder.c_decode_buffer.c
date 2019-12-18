#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {size_t distance; int pos; int /*<<< orphan*/ * history; } ;
typedef  TYPE_1__ lzma_coder ;

/* Variables and functions */

__attribute__((used)) static void
decode_buffer(lzma_coder *coder, uint8_t *buffer, size_t size)
{
	const size_t distance = coder->distance;

	for (size_t i = 0; i < size; ++i) {
		buffer[i] += coder->history[(distance + coder->pos) & 0xFF];
		coder->history[coder->pos-- & 0xFF] = buffer[i];
	}
}