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
 int SWITCH_S1 ; 
 int SWITCH_S2 ; 

int switch_get(int sw) {
    int val = 1;
    switch (sw) {
        case 1: val = SWITCH_S1; break;
        case 2: val = SWITCH_S2; break;
    }
    return val == 0;
}