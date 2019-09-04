#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * ioctl; int /*<<< orphan*/ * write; int /*<<< orphan*/ * read; } ;
typedef  TYPE_1__ mp_stream_p_t ;
struct TYPE_6__ {TYPE_1__* protocol; } ;
typedef  TYPE_2__ mp_obj_type_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;

/* Variables and functions */
 int MP_STREAM_OP_IOCTL ; 
 int MP_STREAM_OP_READ ; 
 int MP_STREAM_OP_WRITE ; 
 TYPE_2__* mp_obj_get_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_raise_msg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mp_type_OSError ; 

const mp_stream_p_t *mp_get_stream_raise(mp_obj_t self_in, int flags) {
    mp_obj_type_t *type = mp_obj_get_type(self_in);
    const mp_stream_p_t *stream_p = type->protocol;
    if (stream_p == NULL
        || ((flags & MP_STREAM_OP_READ) && stream_p->read == NULL)
        || ((flags & MP_STREAM_OP_WRITE) && stream_p->write == NULL)
        || ((flags & MP_STREAM_OP_IOCTL) && stream_p->ioctl == NULL)) {
        // CPython: io.UnsupportedOperation, OSError subclass
        mp_raise_msg(&mp_type_OSError, "stream operation not supported");
    }
    return stream_p;
}