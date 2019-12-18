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
struct dlm_header {int h_version; } ;

/* Variables and functions */
 int DLM_HEADER_SLOTS ; 

int dlm_slots_version(struct dlm_header *h)
{
	if ((h->h_version & 0x0000FFFF) < DLM_HEADER_SLOTS)
		return 0;
	return 1;
}