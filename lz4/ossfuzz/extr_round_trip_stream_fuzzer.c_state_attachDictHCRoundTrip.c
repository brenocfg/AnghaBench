#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* buf; } ;
struct TYPE_7__ {int /*<<< orphan*/  dstream; int /*<<< orphan*/  cstreamHC; int /*<<< orphan*/  level; TYPE_1__ data; } ;
typedef  TYPE_2__ state_t ;
typedef  int /*<<< orphan*/  LZ4_streamHC_t ;

/* Variables and functions */
 int /*<<< orphan*/  LZ4_attach_HC_dictionary (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LZ4_createStreamHC () ; 
 int /*<<< orphan*/  LZ4_freeStreamHC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LZ4_loadDictHC (int /*<<< orphan*/ *,char const*,size_t const) ; 
 int /*<<< orphan*/  LZ4_setCompressionLevel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LZ4_setStreamDecode (int /*<<< orphan*/ ,char const*,size_t const) ; 
 int /*<<< orphan*/  state_extDictHCRoundTrip ; 
 int /*<<< orphan*/  state_prefixHCRoundTrip ; 
 int /*<<< orphan*/  state_randomRoundTrip (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t state_trimDict (TYPE_2__*) ; 

__attribute__((used)) static void state_attachDictHCRoundTrip(state_t* state)
{
    char const* dict = state->data.buf;
    size_t const dictSize = state_trimDict(state);
    LZ4_streamHC_t* dictStream = LZ4_createStreamHC();
    LZ4_setCompressionLevel(dictStream, state->level);
    LZ4_loadDictHC(dictStream, dict, dictSize);
    LZ4_attach_HC_dictionary(state->cstreamHC, dictStream);
    LZ4_setStreamDecode(state->dstream, dict, dictSize);
    state_randomRoundTrip(state, state_prefixHCRoundTrip,
                          state_extDictHCRoundTrip);
    LZ4_freeStreamHC(dictStream);
}