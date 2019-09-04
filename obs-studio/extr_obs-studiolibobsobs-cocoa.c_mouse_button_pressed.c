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
typedef  int obs_key_t ;
typedef  int /*<<< orphan*/  id ;
typedef  int /*<<< orphan*/  SEL ;
typedef  int NSUInteger ;
typedef  scalar_t__ Class ;

/* Variables and functions */
#define  OBS_KEY_MOUSE1 156 
#define  OBS_KEY_MOUSE10 155 
#define  OBS_KEY_MOUSE11 154 
#define  OBS_KEY_MOUSE12 153 
#define  OBS_KEY_MOUSE13 152 
#define  OBS_KEY_MOUSE14 151 
#define  OBS_KEY_MOUSE15 150 
#define  OBS_KEY_MOUSE16 149 
#define  OBS_KEY_MOUSE17 148 
#define  OBS_KEY_MOUSE18 147 
#define  OBS_KEY_MOUSE19 146 
#define  OBS_KEY_MOUSE2 145 
#define  OBS_KEY_MOUSE20 144 
#define  OBS_KEY_MOUSE21 143 
#define  OBS_KEY_MOUSE22 142 
#define  OBS_KEY_MOUSE23 141 
#define  OBS_KEY_MOUSE24 140 
#define  OBS_KEY_MOUSE25 139 
#define  OBS_KEY_MOUSE26 138 
#define  OBS_KEY_MOUSE27 137 
#define  OBS_KEY_MOUSE28 136 
#define  OBS_KEY_MOUSE29 135 
#define  OBS_KEY_MOUSE3 134 
#define  OBS_KEY_MOUSE4 133 
#define  OBS_KEY_MOUSE5 132 
#define  OBS_KEY_MOUSE6 131 
#define  OBS_KEY_MOUSE7 130 
#define  OBS_KEY_MOUSE8 129 
#define  OBS_KEY_MOUSE9 128 
 scalar_t__ objc_getClass (char*) ; 
 int /*<<< orphan*/  objc_msgSend (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sel_registerName (char*) ; 

__attribute__((used)) static bool mouse_button_pressed(obs_key_t key, bool *pressed)
{
	int button = 0;
	switch (key) {
#define MAP_BUTTON(n) case OBS_KEY_MOUSE ## n: button = n - 1; break
	MAP_BUTTON(1);
	MAP_BUTTON(2);
	MAP_BUTTON(3);
	MAP_BUTTON(4);
	MAP_BUTTON(5);
	MAP_BUTTON(6);
	MAP_BUTTON(7);
	MAP_BUTTON(8);
	MAP_BUTTON(9);
	MAP_BUTTON(10);
	MAP_BUTTON(11);
	MAP_BUTTON(12);
	MAP_BUTTON(13);
	MAP_BUTTON(14);
	MAP_BUTTON(15);
	MAP_BUTTON(16);
	MAP_BUTTON(17);
	MAP_BUTTON(18);
	MAP_BUTTON(19);
	MAP_BUTTON(20);
	MAP_BUTTON(21);
	MAP_BUTTON(22);
	MAP_BUTTON(23);
	MAP_BUTTON(24);
	MAP_BUTTON(25);
	MAP_BUTTON(26);
	MAP_BUTTON(27);
	MAP_BUTTON(28);
	MAP_BUTTON(29);
		break;
#undef MAP_BUTTON

	default:
		return false;
	}

	Class NSEvent = objc_getClass("NSEvent");
	SEL pressedMouseButtons = sel_registerName("pressedMouseButtons");
	NSUInteger buttons = (NSUInteger)objc_msgSend((id)NSEvent,
			pressedMouseButtons);

	*pressed = (buttons & (1 << button)) != 0;
	return true;
}