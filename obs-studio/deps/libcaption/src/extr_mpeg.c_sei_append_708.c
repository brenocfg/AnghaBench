#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  timestamp; } ;
typedef  TYPE_1__ sei_t ;
struct TYPE_10__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_2__ sei_message_t ;
typedef  int /*<<< orphan*/  cea708_t ;

/* Variables and functions */
 int /*<<< orphan*/  CEA608_MAX_SIZE ; 
 int /*<<< orphan*/  cea708_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cea708_render (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sei_message_append (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  sei_message_data (TYPE_2__*) ; 
 TYPE_2__* sei_message_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sei_message_size (TYPE_2__*) ; 
 int /*<<< orphan*/  sei_type_user_data_registered_itu_t_t35 ; 

void sei_append_708(sei_t* sei, cea708_t* cea708)
{
    sei_message_t* msg = sei_message_new(sei_type_user_data_registered_itu_t_t35, 0, CEA608_MAX_SIZE);
    msg->size = cea708_render(cea708, sei_message_data(msg), sei_message_size(msg));
    sei_message_append(sei, msg);
    cea708_init(cea708, sei->timestamp); // will confgure using HLS compatiable defaults
}