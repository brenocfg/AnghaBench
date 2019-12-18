#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint16_t ;
typedef  int eia608_style_t ;

/* Variables and functions */
#define  eia608_control_alarm_off 146 
#define  eia608_control_alarm_on 145 
#define  eia608_control_backspace 144 
#define  eia608_control_carriage_return 143 
#define  eia608_control_delete_to_end_of_row 142 
#define  eia608_control_end_of_caption 141 
#define  eia608_control_erase_display_memory 140 
#define  eia608_control_erase_non_displayed_memory 139 
#define  eia608_control_resume_caption_loading 138 
#define  eia608_control_resume_direct_captioning 137 
#define  eia608_control_roll_up_2 136 
#define  eia608_control_roll_up_3 135 
#define  eia608_control_roll_up_4 134 
#define  eia608_control_text_restart 133 
#define  eia608_control_text_resume_text_display 132 
 scalar_t__ eia608_is_basicna (int) ; 
 scalar_t__ eia608_is_control (int) ; 
 scalar_t__ eia608_is_midrowchange (int) ; 
 scalar_t__ eia608_is_norpak (int) ; 
 scalar_t__ eia608_is_preamble (int) ; 
 scalar_t__ eia608_is_specialna (int) ; 
 scalar_t__ eia608_is_westeu (int) ; 
 scalar_t__ eia608_is_xds (int) ; 
 int eia608_parity_strip (int) ; 
 int /*<<< orphan*/  eia608_parity_varify (int) ; 
 int eia608_parse_control (int,int*) ; 
 int /*<<< orphan*/  eia608_parse_preamble (int,int*,int*,int*,int*,int*) ; 
#define  eia608_tab_offset_0 131 
#define  eia608_tab_offset_1 130 
#define  eia608_tab_offset_2 129 
#define  eia608_tab_offset_3 128 
 int /*<<< orphan*/  eia608_to_utf8 (int,int*,char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  stderr ; 

void eia608_dump(uint16_t cc_data)
{
    eia608_style_t style;
    const char* text = 0;
    char char1[5], char2[5];
    char1[0] = char2[0] = 0;
    int row, col, chan, underline;

    if (!eia608_parity_varify(cc_data)) {
        text = "parity failed";
    } else if (0 == eia608_parity_strip(cc_data)) {
        text = "pad";
    } else if (eia608_is_basicna(cc_data)) {
        text = "basicna";
        eia608_to_utf8(cc_data, &chan, &char1[0], &char2[0]);
    } else if (eia608_is_specialna(cc_data)) {
        text = "specialna";
        eia608_to_utf8(cc_data, &chan, &char1[0], &char2[0]);
    } else if (eia608_is_westeu(cc_data)) {
        text = "westeu";
        eia608_to_utf8(cc_data, &chan, &char1[0], &char2[0]);
    } else if (eia608_is_xds(cc_data)) {
        text = "xds";
    } else if (eia608_is_midrowchange(cc_data)) {
        text = "midrowchange";
    } else if (eia608_is_norpak(cc_data)) {
        text = "norpak";
    } else if (eia608_is_preamble(cc_data)) {
        text = "preamble";
        eia608_parse_preamble(cc_data, &row, &col, &style, &chan, &underline);
        fprintf(stderr, "preamble %d %d %d %d %d\n", row, col, style, chan, underline);

    } else if (eia608_is_control(cc_data)) {
        switch (eia608_parse_control(cc_data, &chan)) {

        default:
            text = "unknown_control";
            break;

        case eia608_tab_offset_0:
            text = "eia608_tab_offset_0";
            break;

        case eia608_tab_offset_1:
            text = "eia608_tab_offset_1";
            break;

        case eia608_tab_offset_2:
            text = "eia608_tab_offset_2";
            break;

        case eia608_tab_offset_3:
            text = "eia608_tab_offset_3";
            break;

        case eia608_control_resume_caption_loading:
            text = "eia608_control_resume_caption_loading";
            break;

        case eia608_control_backspace:
            text = "eia608_control_backspace";
            break;

        case eia608_control_alarm_off:
            text = "eia608_control_alarm_off";
            break;

        case eia608_control_alarm_on:
            text = "eia608_control_alarm_on";
            break;

        case eia608_control_delete_to_end_of_row:
            text = "eia608_control_delete_to_end_of_row";
            break;

        case eia608_control_roll_up_2:
            text = "eia608_control_roll_up_2";
            break;

        case eia608_control_roll_up_3:
            text = "eia608_control_roll_up_3";
            break;

        case eia608_control_roll_up_4:
            text = "eia608_control_roll_up_4";
            break;

        case eia608_control_resume_direct_captioning:
            text = "eia608_control_resume_direct_captioning";
            break;

        case eia608_control_text_restart:
            text = "eia608_control_text_restart";
            break;

        case eia608_control_text_resume_text_display:
            text = "eia608_control_text_resume_text_display";
            break;

        case eia608_control_erase_display_memory:
            text = "eia608_control_erase_display_memory";
            break;

        case eia608_control_carriage_return:
            text = "eia608_control_carriage_return";
            break;

        case eia608_control_erase_non_displayed_memory:
            text = "eia608_control_erase_non_displayed_memory";
            break;

        case eia608_control_end_of_caption:
            text = "eia608_control_end_of_caption";
            break;
        }
    } else {
        text = "unhandled";
    }

    fprintf(stderr, "cc %04X (%04X) '%s' '%s' (%s)\n", cc_data, eia608_parity_strip(cc_data), char1, char2, text);
}