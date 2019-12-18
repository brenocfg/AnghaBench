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

/* Variables and functions */
 int /*<<< orphan*/  append_char (unsigned char*,size_t,unsigned int*,char) ; 
 scalar_t__ isalnum (unsigned char) ; 
 scalar_t__ ispunct (unsigned char) ; 

__attribute__((used)) static void
append_name(unsigned char *banner, size_t banner_max, unsigned *banner_length, const unsigned char *name)
{
    unsigned i;
    unsigned char c;

    for (i=0; i<15; i++) {
        c = name[i];

        if (c == 0x20 || c == '\0')
            append_char(banner, banner_max, banner_length, ' ');
        else if (isalnum(c) || ispunct(c))
            append_char(banner, banner_max, banner_length, c);
        else {
            append_char(banner, banner_max, banner_length, '<');
            append_char(banner, banner_max, banner_length, "0123456789ABCDEF"[c>>4]);
            append_char(banner, banner_max, banner_length, "0123456789ABCDEF"[c&0xF]);
            append_char(banner, banner_max, banner_length, '>');
        }
    }

    c = name[i];
    append_char(banner, banner_max, banner_length, '<');
    append_char(banner, banner_max, banner_length, "0123456789ABCDEF"[c>>4]);
    append_char(banner, banner_max, banner_length, "0123456789ABCDEF"[c&0xF]);
    append_char(banner, banner_max, banner_length, '>');
    append_char(banner, banner_max, banner_length, '\n');
}