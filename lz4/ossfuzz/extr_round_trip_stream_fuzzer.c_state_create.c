#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {char const* buf; size_t size; scalar_t__ pos; } ;
struct TYPE_5__ {int /*<<< orphan*/  dstream; int /*<<< orphan*/  cstream; int /*<<< orphan*/  cstreamHC; void* roundTrip; void* compressed; TYPE_1__ data; int /*<<< orphan*/  seed; } ;
typedef  TYPE_2__ state_t ;

/* Variables and functions */
 int /*<<< orphan*/  FUZZ_ASSERT (int /*<<< orphan*/ ) ; 
 int LZ4_compressBound (size_t) ; 
 int /*<<< orphan*/  LZ4_createStream () ; 
 int /*<<< orphan*/  LZ4_createStreamDecode () ; 
 int /*<<< orphan*/  LZ4_createStreamHC () ; 
 void* cursor_create (size_t) ; 

state_t state_create(char const* data, size_t size, uint32_t seed)
{
    state_t state;

    state.seed = seed;

    state.data.buf = (char const*)data;
    state.data.size = size;
    state.data.pos = 0;

    /* Extra margin because we are streaming. */
    state.compressed = cursor_create(1024 + 2 * LZ4_compressBound(size));
    state.roundTrip = cursor_create(size);

    state.cstream = LZ4_createStream();
    FUZZ_ASSERT(state.cstream);
    state.cstreamHC = LZ4_createStreamHC();
    FUZZ_ASSERT(state.cstream);
    state.dstream = LZ4_createStreamDecode();
    FUZZ_ASSERT(state.dstream);

    return state;
}