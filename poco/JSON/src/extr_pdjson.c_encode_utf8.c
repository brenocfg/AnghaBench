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
typedef  int /*<<< orphan*/  json_stream ;

/* Variables and functions */
 int /*<<< orphan*/  json_error (int /*<<< orphan*/ *,char*,unsigned long) ; 
 scalar_t__ pushchar (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int encode_utf8(json_stream *json, unsigned long c)
{
    if (c < 0x80UL) {
        return pushchar(json, c);
    } else if (c < 0x0800UL) {
        return !((pushchar(json, (c >> 6 & 0x1F) | 0xC0) == 0) &&
                 (pushchar(json, (c >> 0 & 0x3F) | 0x80) == 0));
    } else if (c < 0x010000UL) {
        if (c >= 0xd800 && c <= 0xdfff) {
            json_error(json, "invalid codepoint %06lx", c);
            return -1;
        }
        return !((pushchar(json, (c >> 12 & 0x0F) | 0xE0) == 0) &&
                 (pushchar(json, (c >>  6 & 0x3F) | 0x80) == 0) &&
                 (pushchar(json, (c >>  0 & 0x3F) | 0x80) == 0));
    } else if (c < 0x110000UL) {
        return !((pushchar(json, (c >> 18 & 0x07) | 0xF0) == 0) &&
                (pushchar(json, (c >> 12 & 0x3F) | 0x80) == 0) &&
                (pushchar(json, (c >> 6  & 0x3F) | 0x80) == 0) &&
                (pushchar(json, (c >> 0  & 0x3F) | 0x80) == 0));
    } else {
        json_error(json, "can't encode UTF-8 for %06lx", c);
        return -1;
    }
}