#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char* buf; int pos; int size; } ;
struct TYPE_9__ {int size; char* buf; int pos; } ;
struct TYPE_11__ {TYPE_2__ compressed; TYPE_1__ data; int /*<<< orphan*/  cstreamHC; int /*<<< orphan*/  seed; } ;
typedef  TYPE_3__ state_t ;
struct TYPE_12__ {char* buf; } ;
typedef  TYPE_4__ cursor_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,...) ; 
 int /*<<< orphan*/  FUZZ_ASSERT (int) ; 
 int FUZZ_rand32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const) ; 
 int LZ4_compress_HC_continue (int /*<<< orphan*/ ,char const*,char*,int const,int const) ; 
 TYPE_4__ cursor_create (int) ; 
 int /*<<< orphan*/  cursor_free (TYPE_4__) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  state_decompress (TYPE_3__*,char*,int const) ; 

__attribute__((used)) static void state_extDictHCRoundTrip(state_t* state)
{
    int i = 0;
    cursor_t data2 = cursor_create(state->data.size);
    DEBUGLOG(2, "extDictHC");
    memcpy(data2.buf, state->data.buf, state->data.size);
    while (state->data.pos != state->data.size) {
        char const* data = (i++ & 1) ? state->data.buf : data2.buf;
        char const* src = data + state->data.pos;
        char* dst = state->compressed.buf + state->compressed.pos;
        int const srcRemaining = state->data.size - state->data.pos;
        int const srcSize = FUZZ_rand32(&state->seed, 0, srcRemaining);
        int const dstCapacity = state->compressed.size - state->compressed.pos;
        int const cSize = LZ4_compress_HC_continue(state->cstreamHC, src, dst,
                                                   srcSize, dstCapacity);
        FUZZ_ASSERT(cSize > 0);
        DEBUGLOG(2, "srcSize = %d", srcSize);
        state->data.pos += srcSize;
        state->compressed.pos += cSize;
        state_decompress(state, dst, cSize);
    }
    cursor_free(data2);
}