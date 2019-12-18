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
 int SWITCH_S1_TRIS ; 
 int SWITCH_S2_TRIS ; 

void switch_init(void) {
    // set switch GPIO as inputs
    SWITCH_S1_TRIS = 1;
    SWITCH_S2_TRIS = 1;
}