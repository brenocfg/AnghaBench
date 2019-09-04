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
struct uwb_rc {int dummy; } ;

/* Variables and functions */
 int uwb_rc_reset (struct uwb_rc*) ; 

int uwb_radio_setup(struct uwb_rc *rc)
{
	return uwb_rc_reset(rc);
}