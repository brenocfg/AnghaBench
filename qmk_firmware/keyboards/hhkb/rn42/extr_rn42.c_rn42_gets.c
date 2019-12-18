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
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
typedef  int int16_t ;

/* Variables and functions */
 int rn42_getc () ; 
 scalar_t__ timer_elapsed (scalar_t__) ; 
 scalar_t__ timer_read () ; 

const char *rn42_gets(uint16_t timeout)
{
    static char s[24];
    uint16_t t = timer_read();
    uint8_t i = 0;
    int16_t c;
    while (i < 23 && timer_elapsed(t) < timeout) {
        if ((c = rn42_getc()) != -1) {
            if ((char)c == '\r') continue;
            if ((char)c == '\n') break;
            s[i++] = c;
        }
    }
    s[i] = '\0';
    return s;
}