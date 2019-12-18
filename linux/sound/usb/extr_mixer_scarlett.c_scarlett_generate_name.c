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
 size_t SCARLETT_OFFSET_ADAT ; 
 size_t SCARLETT_OFFSET_ANALOG ; 
 size_t SCARLETT_OFFSET_MIX ; 
 size_t SCARLETT_OFFSET_PCM ; 
 size_t SCARLETT_OFFSET_SPDIF ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static void scarlett_generate_name(int i, char *dst, int offsets[])
{
	if (i > offsets[SCARLETT_OFFSET_MIX])
		sprintf(dst, "Mix %c",
			'A'+(i - offsets[SCARLETT_OFFSET_MIX] - 1));
	else if (i > offsets[SCARLETT_OFFSET_ADAT])
		sprintf(dst, "ADAT %d", i - offsets[SCARLETT_OFFSET_ADAT]);
	else if (i > offsets[SCARLETT_OFFSET_SPDIF])
		sprintf(dst, "SPDIF %d", i - offsets[SCARLETT_OFFSET_SPDIF]);
	else if (i > offsets[SCARLETT_OFFSET_ANALOG])
		sprintf(dst, "Analog %d", i - offsets[SCARLETT_OFFSET_ANALOG]);
	else if (i > offsets[SCARLETT_OFFSET_PCM])
		sprintf(dst, "PCM %d", i - offsets[SCARLETT_OFFSET_PCM]);
	else
		sprintf(dst, "Off");
}