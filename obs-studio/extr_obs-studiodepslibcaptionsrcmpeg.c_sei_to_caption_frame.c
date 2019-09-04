#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  timestamp; } ;
typedef  TYPE_1__ sei_t ;
typedef  int /*<<< orphan*/  sei_message_t ;
typedef  scalar_t__ libcaption_stauts_t ;
typedef  int /*<<< orphan*/  cea708_t ;
struct TYPE_8__ {int /*<<< orphan*/  timestamp; } ;
typedef  TYPE_2__ caption_frame_t ;

/* Variables and functions */
 scalar_t__ LIBCAPTION_OK ; 
 scalar_t__ LIBCAPTION_READY ; 
 int /*<<< orphan*/  cea708_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cea708_parse_h264 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cea708_to_caption_frame (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ libcaption_status_update (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sei_message_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sei_message_head (TYPE_1__*) ; 
 int /*<<< orphan*/ * sei_message_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sei_message_size (int /*<<< orphan*/ *) ; 
 scalar_t__ sei_message_type (int /*<<< orphan*/ *) ; 
 scalar_t__ sei_type_user_data_registered_itu_t_t35 ; 

libcaption_stauts_t sei_to_caption_frame(sei_t* sei, caption_frame_t* frame)
{
    cea708_t cea708;
    sei_message_t* msg;
    libcaption_stauts_t status = LIBCAPTION_OK;

    cea708_init(&cea708, frame->timestamp);

    for (msg = sei_message_head(sei); msg; msg = sei_message_next(msg)) {
        if (sei_type_user_data_registered_itu_t_t35 == sei_message_type(msg)) {
            cea708_parse_h264(sei_message_data(msg), sei_message_size(msg), &cea708);
            status = libcaption_status_update(status, cea708_to_caption_frame(frame, &cea708));
        }
    }

    if (LIBCAPTION_READY == status) {
        frame->timestamp = sei->timestamp;
    }

    return status;
}