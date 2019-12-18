#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* head; } ;
typedef  TYPE_1__ sei_t ;
struct TYPE_7__ {struct TYPE_7__* next; } ;
typedef  TYPE_2__ sei_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  sei_init (TYPE_1__*,int /*<<< orphan*/ ) ; 

void sei_free(sei_t* sei)
{
    sei_message_t* tail;

    while (sei->head) {
        tail = sei->head->next;
        free(sei->head);
        sei->head = tail;
    }

    sei_init(sei, 0);
}