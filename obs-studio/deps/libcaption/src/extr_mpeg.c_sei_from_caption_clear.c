#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  timestamp; } ;
typedef  TYPE_1__ sei_t ;
typedef  int /*<<< orphan*/  libcaption_stauts_t ;
typedef  int /*<<< orphan*/  cea708_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_CHANNEL ; 
 int /*<<< orphan*/  LIBCAPTION_OK ; 
 int /*<<< orphan*/  cc_type_ntsc_cc_field_1 ; 
 int /*<<< orphan*/  cea708_add_cc_data (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cea708_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eia608_control_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eia608_control_end_of_caption ; 
 int /*<<< orphan*/  eia608_control_erase_display_memory ; 
 int /*<<< orphan*/  eia608_control_erase_non_displayed_memory ; 
 int /*<<< orphan*/  sei_append_708 (TYPE_1__*,int /*<<< orphan*/ *) ; 

libcaption_stauts_t sei_from_caption_clear(sei_t* sei)
{
    cea708_t cea708;
    cea708_init(&cea708, sei->timestamp); // set up a new popon frame
    cea708_add_cc_data(&cea708, 1, cc_type_ntsc_cc_field_1, eia608_control_command(eia608_control_end_of_caption, DEFAULT_CHANNEL));
    cea708_add_cc_data(&cea708, 1, cc_type_ntsc_cc_field_1, eia608_control_command(eia608_control_end_of_caption, DEFAULT_CHANNEL));
    cea708_add_cc_data(&cea708, 1, cc_type_ntsc_cc_field_1, eia608_control_command(eia608_control_erase_non_displayed_memory, DEFAULT_CHANNEL));
    cea708_add_cc_data(&cea708, 1, cc_type_ntsc_cc_field_1, eia608_control_command(eia608_control_erase_non_displayed_memory, DEFAULT_CHANNEL));
    cea708_add_cc_data(&cea708, 1, cc_type_ntsc_cc_field_1, eia608_control_command(eia608_control_erase_display_memory, DEFAULT_CHANNEL));
    cea708_add_cc_data(&cea708, 1, cc_type_ntsc_cc_field_1, eia608_control_command(eia608_control_erase_display_memory, DEFAULT_CHANNEL));
    sei_append_708(sei, &cea708);
    return LIBCAPTION_OK;
}