#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  head; } ;
typedef  TYPE_1__ sei_t ;
struct TYPE_9__ {int type; int size; } ;
typedef  TYPE_2__ sei_message_t ;

/* Variables and functions */
 TYPE_2__* sei_message_head (TYPE_1__*) ; 
 TYPE_2__* sei_message_next (TYPE_2__*) ; 

size_t sei_render_size(sei_t* sei)
{
    if (!sei || !sei->head) {
        return 0;
    }

    size_t size = 2; // nalu_type + stop bit
    sei_message_t* msg;
    for (msg = sei_message_head(sei); msg; msg = sei_message_next(msg)) {
        size += 1 + (msg->type / 255);
        size += 1 + (msg->size / 255);
        size += 1 + (msg->size * 4 / 3);
    }

    return size;
}