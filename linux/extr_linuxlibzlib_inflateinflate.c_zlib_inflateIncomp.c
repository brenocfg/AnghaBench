#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned char* next_out; scalar_t__ avail_in; scalar_t__ next_in; scalar_t__ total_in; scalar_t__ total_out; int /*<<< orphan*/  adler; int /*<<< orphan*/  avail_out; scalar_t__ state; } ;
typedef  TYPE_1__ z_stream ;
typedef  int /*<<< orphan*/  uInt ;
struct inflate_state {scalar_t__ mode; scalar_t__ total; int /*<<< orphan*/  check; } ;
typedef  unsigned char Byte ;

/* Variables and functions */
 scalar_t__ HEAD ; 
 scalar_t__ TYPE ; 
 int /*<<< orphan*/  UPDATE (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int Z_DATA_ERROR ; 
 int Z_OK ; 
 int /*<<< orphan*/  zlib_updatewindow (TYPE_1__*,scalar_t__) ; 

int zlib_inflateIncomp(z_stream *z)
{
    struct inflate_state *state = (struct inflate_state *)z->state;
    Byte *saved_no = z->next_out;
    uInt saved_ao = z->avail_out;

    if (state->mode != TYPE && state->mode != HEAD)
	return Z_DATA_ERROR;

    /* Setup some variables to allow misuse of updateWindow */
    z->avail_out = 0;
    z->next_out = (unsigned char*)z->next_in + z->avail_in;

    zlib_updatewindow(z, z->avail_in);

    /* Restore saved variables */
    z->avail_out = saved_ao;
    z->next_out = saved_no;

    z->adler = state->check =
        UPDATE(state->check, z->next_in, z->avail_in);

    z->total_out += z->avail_in;
    z->total_in += z->avail_in;
    z->next_in += z->avail_in;
    state->total += z->avail_in;
    z->avail_in = 0;

    return Z_OK;
}