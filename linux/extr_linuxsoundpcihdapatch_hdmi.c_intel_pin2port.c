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
 scalar_t__ WARN_ON (int) ; 
 int intel_base_nid (void*) ; 

__attribute__((used)) static int intel_pin2port(void *audio_ptr, int pin_nid)
{
	int base_nid = intel_base_nid(audio_ptr);

	if (WARN_ON(pin_nid < base_nid || pin_nid >= base_nid + 3))
		return -1;
	return pin_nid - base_nid + 1; /* intel port is 1-based */
}