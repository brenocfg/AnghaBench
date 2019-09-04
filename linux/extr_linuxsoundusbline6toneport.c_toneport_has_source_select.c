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
struct usb_line6_toneport {int type; } ;

/* Variables and functions */
#define  LINE6_PODSTUDIO_UX1 131 
#define  LINE6_PODSTUDIO_UX2 130 
#define  LINE6_TONEPORT_UX1 129 
#define  LINE6_TONEPORT_UX2 128 

__attribute__((used)) static bool toneport_has_source_select(struct usb_line6_toneport *toneport)
{
	switch (toneport->type) {
	case LINE6_TONEPORT_UX1:
	case LINE6_TONEPORT_UX2:
	case LINE6_PODSTUDIO_UX1:
	case LINE6_PODSTUDIO_UX2:
		return true;

	default:
		return false;
	}
}