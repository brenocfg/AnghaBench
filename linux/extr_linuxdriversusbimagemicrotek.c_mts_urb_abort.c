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
struct mts_desc {int /*<<< orphan*/  urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTS_DEBUG_GOT_HERE () ; 
 int /*<<< orphan*/  mts_debug_dump (struct mts_desc*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mts_urb_abort(struct mts_desc* desc) {
	MTS_DEBUG_GOT_HERE();
	mts_debug_dump(desc);

	usb_kill_urb( desc->urb );
}