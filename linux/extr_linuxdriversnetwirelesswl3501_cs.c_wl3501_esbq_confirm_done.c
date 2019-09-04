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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  tmp ;
struct wl3501_card {scalar_t__ esbq_confirm; scalar_t__ esbq_confirm_end; scalar_t__ esbq_confirm_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  wl3501_set_to_wla (struct wl3501_card*,scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void wl3501_esbq_confirm_done(struct wl3501_card *this)
{
	u8 tmp = 0;

	wl3501_set_to_wla(this, this->esbq_confirm + 3, &tmp, sizeof(tmp));
	this->esbq_confirm += 4;
	if (this->esbq_confirm >= this->esbq_confirm_end)
		this->esbq_confirm = this->esbq_confirm_start;
}