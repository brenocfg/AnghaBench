#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t const pos; int /*<<< orphan*/  buf; } ;
struct TYPE_5__ {char* buf; size_t size; } ;
struct TYPE_7__ {TYPE_2__ roundTrip; TYPE_1__ data; } ;
typedef  TYPE_3__ state_t ;

/* Variables and functions */
 int /*<<< orphan*/  FUZZ_ASSERT_MSG (int,char*) ; 
 int /*<<< orphan*/  memcmp (char const*,int /*<<< orphan*/ ,size_t const) ; 

__attribute__((used)) static void state_checkRoundTrip(state_t const* state)
{
    char const* data = state->data.buf;
    size_t const size = state->data.size;
    FUZZ_ASSERT_MSG(size == state->roundTrip.pos, "Incorrect size!");
    FUZZ_ASSERT_MSG(!memcmp(data, state->roundTrip.buf, size), "Corruption!");
}