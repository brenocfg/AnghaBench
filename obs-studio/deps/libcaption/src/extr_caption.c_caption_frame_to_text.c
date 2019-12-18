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
typedef  char utf8_char_t ;
typedef  int /*<<< orphan*/  eia608_style_t ;
typedef  int /*<<< orphan*/  caption_frame_t ;

/* Variables and functions */
 int SCREEN_COLS ; 
 int SCREEN_ROWS ; 
 char* caption_frame_read_char (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 size_t utf8_char_copy (char*,char const*) ; 
 scalar_t__ utf8_char_length (char const*) ; 
 int /*<<< orphan*/  utf8_char_whitespace (char const*) ; 

size_t caption_frame_to_text(caption_frame_t* frame, utf8_char_t* data)
{
    int r, c, uln, crlf = 0, count = 0;
    size_t s, size = 0;
    eia608_style_t sty;
    (*data) = '\0';

    for (r = 0; r < SCREEN_ROWS; ++r) {
        crlf += count, count = 0;
        for (c = 0; c < SCREEN_COLS; ++c) {
            const utf8_char_t* chr = caption_frame_read_char(frame, r, c, &sty, &uln);
            // dont start a new line until we encounter at least one printable character
            if (0 < utf8_char_length(chr) && (0 < count || !utf8_char_whitespace(chr))) {
                if (0 < crlf) {
                    memcpy(data, "\r\n\0", 3);
                    data += 2, size += 2, crlf = 0;
                }

                s = utf8_char_copy(data, chr);
                data += s, size += s, ++count;
            }
        }
    }

    return size;
}