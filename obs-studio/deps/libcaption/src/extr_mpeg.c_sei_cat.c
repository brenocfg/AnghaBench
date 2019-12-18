#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sei_t ;
struct TYPE_6__ {scalar_t__ type; } ;
typedef  TYPE_1__ sei_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  sei_message_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sei_message_copy (TYPE_1__*) ; 
 TYPE_1__* sei_message_head (int /*<<< orphan*/ *) ; 
 TYPE_1__* sei_message_next (TYPE_1__*) ; 
 scalar_t__ sei_type_user_data_registered_itu_t_t35 ; 

void sei_cat(sei_t* to, sei_t* from, int itu_t_t35)
{
    if (!to || !from) {
        return;
    }

    sei_message_t* msg = NULL;
    for (msg = sei_message_head(from); msg; msg = sei_message_next(msg)) {
        if (itu_t_t35 || sei_type_user_data_registered_itu_t_t35 != msg->type) {
            sei_message_append(to, sei_message_copy(msg));
        }
    }
}