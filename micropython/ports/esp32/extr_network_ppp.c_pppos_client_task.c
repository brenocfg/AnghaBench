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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u8_t ;
struct TYPE_2__ {int /*<<< orphan*/ * client_task_handle; int /*<<< orphan*/  pcb; int /*<<< orphan*/  stream; } ;
typedef  TYPE_1__ ppp_if_obj_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int mp_stream_rw (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdTRUE ; 
 int /*<<< orphan*/  pppos_input_tcpip (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ulTaskNotifyTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pppos_client_task(void *self_in) {
    ppp_if_obj_t *self = (ppp_if_obj_t*)self_in;
    uint8_t buf[256];

    while (ulTaskNotifyTake(pdTRUE, 0) == 0) {
        int err;
        int len = mp_stream_rw(self->stream, buf, sizeof(buf), &err, 0);
        if (len > 0) {
            pppos_input_tcpip(self->pcb, (u8_t*)buf, len);
        }
    }

    self->client_task_handle = NULL;
    vTaskDelete(NULL);
}