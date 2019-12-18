#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_FROM_PTR (void*) ; 
 int /*<<< orphan*/  MP_STREAM_RW_WRITE ; 
 int /*<<< orphan*/  mp_stream_write (int /*<<< orphan*/ ,char const*,size_t,int /*<<< orphan*/ ) ; 

void mp_stream_write_adaptor(void *self, const char *buf, size_t len) {
    mp_stream_write(MP_OBJ_FROM_PTR(self), buf, len, MP_STREAM_RW_WRITE);
}