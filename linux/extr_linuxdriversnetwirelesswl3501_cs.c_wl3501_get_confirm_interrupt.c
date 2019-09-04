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
typedef  int /*<<< orphan*/  u16 ;
struct wl3501_card {int /*<<< orphan*/  wait; int /*<<< orphan*/  sig_get_confirm; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl3501_get_from_wla (struct wl3501_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void wl3501_get_confirm_interrupt(struct wl3501_card *this,
						u16 addr, void *sig, int size)
{
	pr_debug("entry");
	wl3501_get_from_wla(this, addr, &this->sig_get_confirm,
			    sizeof(this->sig_get_confirm));
	wake_up(&this->wait);
}