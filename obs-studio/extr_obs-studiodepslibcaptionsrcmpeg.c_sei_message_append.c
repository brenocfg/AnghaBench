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
struct TYPE_5__ {TYPE_2__* tail; TYPE_2__* head; } ;
typedef  TYPE_1__ sei_t ;
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_2__ sei_message_t ;

/* Variables and functions */

void sei_message_append(sei_t* sei, sei_message_t* msg)
{
    if (0 == sei->head) {
        sei->head = msg;
        sei->tail = msg;
    } else {
        sei->tail->next = msg;
        sei->tail = msg;
    }
}