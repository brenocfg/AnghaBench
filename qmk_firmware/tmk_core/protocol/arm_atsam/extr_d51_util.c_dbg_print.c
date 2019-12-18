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
typedef  int uint32_t ;
typedef  int int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_1_OFF ; 
 int /*<<< orphan*/  DBG_1_ON ; 
 scalar_t__ DBG_PAUSE ; 
 scalar_t__ w ; 

void dbg_print(uint32_t x) {
    int8_t   t;
    uint32_t n;
    uint32_t p, p2;

    if (x < 10)
        t = 0;
    else if (x < 100)
        t = 1;
    else if (x < 1000)
        t = 2;
    else if (x < 10000)
        t = 3;
    else if (x < 100000)
        t = 4;
    else if (x < 1000000)
        t = 5;
    else if (x < 10000000)
        t = 6;
    else if (x < 100000000)
        t = 7;
    else if (x < 1000000000)
        t = 8;
    else
        t = 9;

    while (t >= 0) {
        p2 = t;
        p  = 1;
        while (p2--) p *= 10;
        n = x / p;
        x -= n * p;
        if (!n) {
            DBG_1_ON;
            DBG_1_OFF;
            DBG_1_ON;
            DBG_1_OFF;
            n--;
        } else {
            while (n > 0) {
                DBG_1_ON;
                DBG_1_OFF;
                n--;
            }
        }

        t--;
    }

    for (w = DBG_PAUSE; w; w--)
        ;  // Long pause after number is complete
}