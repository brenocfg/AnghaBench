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
typedef  scalar_t__ ut8 ;

/* Variables and functions */
 scalar_t__ GB_GBC ; 
 scalar_t__ GB_SGB ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

void gb_get_gbtype(char *type, ut8 foo, ut8 bar){
	if (foo==GB_SGB) {
		strcpy (type, "SuperGameboy-Rom");
	} else {
		if (bar==GB_GBC) {
			strcpy (type, "GameboyColor-Rom");
		} else {
			strcpy (type, "Gameboy-Rom");
		}
	}
}