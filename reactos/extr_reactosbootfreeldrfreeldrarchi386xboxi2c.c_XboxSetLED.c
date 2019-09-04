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
typedef  char* PCSTR ;

/* Variables and functions */
 int /*<<< orphan*/  I2cSetFrontpanelLed (int) ; 
 int strlen (char*) ; 

void
XboxSetLED(PCSTR pattern) {
    const char *x = pattern;
    int r, g;

    if(strlen(pattern) == 4) {
        r = g = 0;
        while (*x) {
            r *= 2;
            g *= 2;
            switch (*x) {
                case 'r':
                    r++;
                    break;
                case 'g':
                    g++;
                    break;
                case 'o':
                    r++;
                    g++;
                    break;
            }
            x++;
        }
        I2cSetFrontpanelLed(((r<<4) & 0xF0) + (g & 0xF));
    }
}