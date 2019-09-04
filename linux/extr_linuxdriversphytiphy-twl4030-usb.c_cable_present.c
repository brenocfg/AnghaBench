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
typedef  enum musb_vbus_id_status { ____Placeholder_musb_vbus_id_status } musb_vbus_id_status ;

/* Variables and functions */
 int MUSB_ID_GROUND ; 
 int MUSB_VBUS_VALID ; 

__attribute__((used)) static inline bool cable_present(enum musb_vbus_id_status stat)
{
	return stat == MUSB_VBUS_VALID ||
		stat == MUSB_ID_GROUND;
}