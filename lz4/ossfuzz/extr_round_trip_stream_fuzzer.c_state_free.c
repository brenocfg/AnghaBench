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
struct TYPE_3__ {int /*<<< orphan*/  dstream; int /*<<< orphan*/  cstreamHC; int /*<<< orphan*/  cstream; int /*<<< orphan*/  roundTrip; int /*<<< orphan*/  compressed; } ;
typedef  TYPE_1__ state_t ;

/* Variables and functions */
 int /*<<< orphan*/  LZ4_freeStream (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LZ4_freeStreamDecode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LZ4_freeStreamHC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cursor_free (int /*<<< orphan*/ ) ; 

void state_free(state_t state)
{
    cursor_free(state.compressed);
    cursor_free(state.roundTrip);
    LZ4_freeStream(state.cstream);
    LZ4_freeStreamHC(state.cstreamHC);
    LZ4_freeStreamDecode(state.dstream);
}