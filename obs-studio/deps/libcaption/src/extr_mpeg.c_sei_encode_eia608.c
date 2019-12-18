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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  sei_t ;
struct TYPE_6__ {int cc_count; } ;
struct TYPE_7__ {TYPE_1__ user_data; } ;
typedef  TYPE_2__ cea708_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_CHANNEL ; 
 int /*<<< orphan*/  cc_type_ntsc_cc_field_1 ; 
 int /*<<< orphan*/  cea708_add_cc_data (TYPE_2__*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ eia608_control_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eia608_control_end_of_caption ; 
 int /*<<< orphan*/  eia608_control_resume_caption_loading ; 
 int /*<<< orphan*/  sei_append_708 (int /*<<< orphan*/ *,TYPE_2__*) ; 

void sei_encode_eia608(sei_t* sei, cea708_t* cea708, uint16_t cc_data)
{
    // This one is full, flush and init a new one
    // shoudl this be 32? I cant remember
    if (31 == cea708->user_data.cc_count) {
        sei_append_708(sei, cea708);
    }

    if (0 == cea708->user_data.cc_count) { // This is a new 708 header, but a continuation of a 608 stream
        cea708_add_cc_data(cea708, 1, cc_type_ntsc_cc_field_1, eia608_control_command(eia608_control_resume_caption_loading, DEFAULT_CHANNEL));
        cea708_add_cc_data(cea708, 1, cc_type_ntsc_cc_field_1, eia608_control_command(eia608_control_resume_caption_loading, DEFAULT_CHANNEL));
    }

    if (0 == cc_data) { // Finished
        sei_encode_eia608(sei, cea708, eia608_control_command(eia608_control_end_of_caption, DEFAULT_CHANNEL));
        sei_encode_eia608(sei, cea708, eia608_control_command(eia608_control_end_of_caption, DEFAULT_CHANNEL));
        sei_append_708(sei, cea708);
        return;
    }

    cea708_add_cc_data(cea708, 1, cc_type_ntsc_cc_field_1, cc_data);
}