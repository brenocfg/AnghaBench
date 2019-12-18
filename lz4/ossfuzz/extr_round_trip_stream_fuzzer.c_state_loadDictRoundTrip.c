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
struct TYPE_7__ {int /*<<< orphan*/  dstream; int /*<<< orphan*/  cstream; TYPE_1__ data; } ;
typedef  TYPE_2__ state_t ;

/* Variables and functions */
 int /*<<< orphan*/  LZ4_loadDict (int /*<<< orphan*/ ,char const*,size_t const) ; 
 int /*<<< orphan*/  LZ4_setStreamDecode (int /*<<< orphan*/ ,char const*,size_t const) ; 
 int /*<<< orphan*/  state_extDictRoundTrip ; 
 int /*<<< orphan*/  state_prefixRoundTrip ; 
 int /*<<< orphan*/  state_randomRoundTrip (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t state_trimDict (TYPE_2__*) ; 

__attribute__((used)) static void state_loadDictRoundTrip(state_t* state)
{
    char const* dict = state->data.buf;
    size_t const dictSize = state_trimDict(state);
    LZ4_loadDict(state->cstream, dict, dictSize);
    LZ4_setStreamDecode(state->dstream, dict, dictSize);
    state_randomRoundTrip(state, state_prefixRoundTrip, state_extDictRoundTrip);
}