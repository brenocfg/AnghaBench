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
typedef  int uint16_t ;

/* Variables and functions */
 int ACTION_FUNCTION_TAP (int) ; 
#define  TRIPLE_TAP_1_3 129 
#define  TRIPLE_TAP_2_3 128 
 int /*<<< orphan*/ * fn_actions ; 
 int pgm_read_word (int /*<<< orphan*/ *) ; 

uint16_t keymap_function_id_to_action( uint16_t function_id )
{
	// Zeal60 specific "action functions" are 0xF00 to 0xFFF
	// i.e. F(0xF00) to F(0xFFF) are mapped to
	// enum zeal60_action_functions by masking last 8 bits.
	if ( function_id >= 0x0F00 && function_id <= 0x0FFF )
	{
		uint8_t id = function_id & 0xFF;
		switch ( id ) {
			case TRIPLE_TAP_1_3:
			case TRIPLE_TAP_2_3:
			{
				return ACTION_FUNCTION_TAP(id);
				break;
			}
			default:
				break;
		}
	}

	return pgm_read_word(&fn_actions[function_id]);
}