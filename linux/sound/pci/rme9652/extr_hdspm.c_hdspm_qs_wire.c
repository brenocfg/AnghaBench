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
struct hdspm {int control_register; } ;

/* Variables and functions */
 int HDSPM_QS_DoubleWire ; 
 int HDSPM_QS_QuadWire ; 

__attribute__((used)) static int hdspm_qs_wire(struct hdspm * hdspm)
{
	if (hdspm->control_register & HDSPM_QS_DoubleWire)
		return 1;
	if (hdspm->control_register & HDSPM_QS_QuadWire)
		return 2;
	return 0;
}