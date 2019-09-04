#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8_t ;
typedef  int /*<<< orphan*/  u32_t ;
typedef  int /*<<< orphan*/  ppp_pcb ;
struct TYPE_2__ {int /*<<< orphan*/  stream; } ;
typedef  TYPE_1__ ppp_if_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_STREAM_RW_WRITE ; 
 int /*<<< orphan*/  mp_stream_rw (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32_t ppp_output_callback(ppp_pcb *pcb, u8_t *data, u32_t len, void *ctx) {
    ppp_if_obj_t *self = ctx;
    int err;
    return mp_stream_rw(self->stream, data, len, &err, MP_STREAM_RW_WRITE);
}