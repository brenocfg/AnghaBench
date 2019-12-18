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
 int /*<<< orphan*/  UC_LNX ; 
 int /*<<< orphan*/  set_unicode_input_mode (int /*<<< orphan*/ ) ; 

void eeconfig_init_user (void) {
	set_unicode_input_mode(UC_LNX); // Linux
	//set_unicode_input_mode(UC_OSX); // Mac OSX
	//set_unicode_input_mode(UC_WIN); // Windows (with registry key, see wiki)
	//set_unicode_input_mode(UC_WINC); // Windows (with WinCompose, see wiki)
}