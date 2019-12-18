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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
#define  DF 129 
#define  FN 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom (int,int,int) ; 

uint32_t layer_state_set_user(uint32_t state)
{
	uint8_t layer=biton32(state);
	switch(layer)
	{
		case DF:
			rgblight_sethsv_noeeprom(180,255,255);
			break;
		case FN:
			rgblight_sethsv_noeeprom(0,255,255);
			break;
		default:
			break;
	}
	return state;
}