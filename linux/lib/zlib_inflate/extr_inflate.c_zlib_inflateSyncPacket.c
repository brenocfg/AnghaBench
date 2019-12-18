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
typedef  TYPE_1__* z_streamp ;
struct inflate_state {scalar_t__ mode; scalar_t__ bits; } ;
struct TYPE_3__ {int /*<<< orphan*/ * state; } ;

/* Variables and functions */
 scalar_t__ STORED ; 
 scalar_t__ TYPE ; 
 int Z_DATA_ERROR ; 
 int Z_OK ; 
 int Z_STREAM_ERROR ; 

__attribute__((used)) static int zlib_inflateSyncPacket(z_streamp strm)
{
    struct inflate_state *state;

    if (strm == NULL || strm->state == NULL) return Z_STREAM_ERROR;
    state = (struct inflate_state *)strm->state;

    if (state->mode == STORED && state->bits == 0) {
	state->mode = TYPE;
        return Z_OK;
    }
    return Z_DATA_ERROR;
}