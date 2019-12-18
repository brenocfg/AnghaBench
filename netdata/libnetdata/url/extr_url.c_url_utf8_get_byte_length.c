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
 int /*<<< orphan*/  IS_UTF8_BYTE (char) ; 
 scalar_t__ likely (char) ; 

char url_utf8_get_byte_length(char c) {
    if(!IS_UTF8_BYTE(c))
        return 1;

    char length = 0;
    while(likely(c & 0x80)) {
        length++;
        c <<= 1;
    }
    //4 byte is max size for UTF-8 char
    //10XX XXXX is not valid character -> check length == 1
    if(length > 4 || length == 1)
        return -1;

    return length;
}