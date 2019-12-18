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
struct bstr {int len; scalar_t__* start; } ;

/* Variables and functions */
 scalar_t__ bstr_decode_utf8 (struct bstr,struct bstr*) ; 
 int bstr_parse_utf8_code_length (unsigned int) ; 

int bstr_validate_utf8(struct bstr s)
{
    while (s.len) {
        if (bstr_decode_utf8(s, &s) < 0) {
            // Try to guess whether the sequence was just cut-off.
            unsigned int codepoint = (unsigned char)s.start[0];
            int bytes = bstr_parse_utf8_code_length(codepoint);
            if (bytes > 1 && s.len < 6) {
                // Manually check validity of left bytes
                for (int n = 1; n < bytes; n++) {
                    if (n >= s.len) {
                        // Everything valid until now - just cut off.
                        return -(bytes - s.len);
                    }
                    int tmp = (unsigned char)s.start[n];
                    if ((tmp & 0xC0) != 0x80)
                        break;
                }
            }
            return -8;
        }
    }
    return 0;
}