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
typedef  float uint8_t ;

/* Variables and functions */
 float MAX (float,float) ; 
 float TYPING_SPEED_MAX_VALUE ; 
 scalar_t__ typing_speed ; 

uint8_t velocikey_match_speed(uint8_t minValue, uint8_t maxValue) { return MAX(minValue, maxValue - (maxValue - minValue) * ((float)typing_speed / TYPING_SPEED_MAX_VALUE)); }