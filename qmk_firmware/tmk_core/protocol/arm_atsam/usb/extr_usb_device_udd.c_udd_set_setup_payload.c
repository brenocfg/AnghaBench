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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  payload_size; int /*<<< orphan*/ * payload; } ;

/* Variables and functions */
 TYPE_1__ udd_g_ctrlreq ; 

void udd_set_setup_payload(uint8_t *payload, uint16_t payload_size) {
    udd_g_ctrlreq.payload      = payload;
    udd_g_ctrlreq.payload_size = payload_size;
}