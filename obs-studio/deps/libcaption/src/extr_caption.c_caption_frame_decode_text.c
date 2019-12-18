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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  libcaption_stauts_t ;
typedef  int /*<<< orphan*/  caption_frame_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIBCAPTION_OK ; 
 int /*<<< orphan*/  caption_frame_backspace (int /*<<< orphan*/ *) ; 
 scalar_t__ eia608_is_westeu (int /*<<< orphan*/ ) ; 
 size_t eia608_to_utf8 (int /*<<< orphan*/ ,int*,char*,char*) ; 
 int /*<<< orphan*/  eia608_write_char (int /*<<< orphan*/ *,char*) ; 

libcaption_stauts_t caption_frame_decode_text(caption_frame_t* frame, uint16_t cc_data)
{
    int chan;
    char char1[5], char2[5];
    size_t chars = eia608_to_utf8(cc_data, &chan, &char1[0], &char2[0]);

    if (eia608_is_westeu(cc_data)) {
        // Extended charcters replace the previous charcter for back compatibility
        caption_frame_backspace(frame);
    }

    if (0 < chars) {
        eia608_write_char(frame, char1);
    }

    if (1 < chars) {
        eia608_write_char(frame, char2);
    }

    return LIBCAPTION_OK;
}