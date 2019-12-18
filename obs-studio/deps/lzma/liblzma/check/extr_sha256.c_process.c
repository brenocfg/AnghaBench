#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {int /*<<< orphan*/  state; } ;
struct TYPE_7__ {TYPE_3__ sha256; } ;
struct TYPE_6__ {int /*<<< orphan*/ * u32; } ;
struct TYPE_9__ {TYPE_2__ state; TYPE_1__ buffer; } ;
typedef  TYPE_4__ lzma_check_state ;

/* Variables and functions */
 int /*<<< orphan*/  bswap32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transform (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
process(lzma_check_state *check)
{
#ifdef WORDS_BIGENDIAN
	transform(check->state.sha256.state, check->buffer.u32);

#else
	uint32_t data[16];

	for (size_t i = 0; i < 16; ++i)
		data[i] = bswap32(check->buffer.u32[i]);

	transform(check->state.sha256.state, data);
#endif

	return;
}