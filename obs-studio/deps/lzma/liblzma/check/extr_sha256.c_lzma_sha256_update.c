#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int size; } ;
struct TYPE_9__ {TYPE_2__ sha256; } ;
struct TYPE_7__ {scalar_t__ u8; } ;
struct TYPE_10__ {TYPE_3__ state; TYPE_1__ buffer; } ;
typedef  TYPE_4__ lzma_check_state ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  process (TYPE_4__*) ; 

extern void
lzma_sha256_update(const uint8_t *buf, size_t size, lzma_check_state *check)
{
	// Copy the input data into a properly aligned temporary buffer.
	// This way we can be called with arbitrarily sized buffers
	// (no need to be multiple of 64 bytes), and the code works also
	// on architectures that don't allow unaligned memory access.
	while (size > 0) {
		const size_t copy_start = check->state.sha256.size & 0x3F;
		size_t copy_size = 64 - copy_start;
		if (copy_size > size)
			copy_size = size;

		memcpy(check->buffer.u8 + copy_start, buf, copy_size);

		buf += copy_size;
		size -= copy_size;
		check->state.sha256.size += copy_size;

		if ((check->state.sha256.size & 0x3F) == 0)
			process(check);
	}

	return;
}