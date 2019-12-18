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
typedef  int /*<<< orphan*/  vstr_t ;
typedef  int unichar ;
typedef  int byte ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vstr_add_byte (int /*<<< orphan*/ *,int) ; 
 scalar_t__ vstr_add_len (int /*<<< orphan*/ *,int) ; 

void vstr_add_char(vstr_t *vstr, unichar c) {
#if MICROPY_PY_BUILTINS_STR_UNICODE
    // TODO: Can this be simplified and deduplicated?
    // Is it worth just calling vstr_add_len(vstr, 4)?
    if (c < 0x80) {
        byte *buf = (byte*)vstr_add_len(vstr, 1);
        *buf = (byte)c;
    } else if (c < 0x800) {
        byte *buf = (byte*)vstr_add_len(vstr, 2);
        buf[0] = (c >> 6) | 0xC0;
        buf[1] = (c & 0x3F) | 0x80;
    } else if (c < 0x10000) {
        byte *buf = (byte*)vstr_add_len(vstr, 3);
        buf[0] = (c >> 12) | 0xE0;
        buf[1] = ((c >> 6) & 0x3F) | 0x80;
        buf[2] = (c & 0x3F) | 0x80;
    } else {
        assert(c < 0x110000);
        byte *buf = (byte*)vstr_add_len(vstr, 4);
        buf[0] = (c >> 18) | 0xF0;
        buf[1] = ((c >> 12) & 0x3F) | 0x80;
        buf[2] = ((c >> 6) & 0x3F) | 0x80;
        buf[3] = (c & 0x3F) | 0x80;
    }
#else
    vstr_add_byte(vstr, c);
#endif
}