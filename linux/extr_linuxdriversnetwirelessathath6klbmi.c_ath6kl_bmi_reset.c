#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int done_sent; } ;
struct ath6kl {TYPE_1__ bmi; } ;

/* Variables and functions */

void ath6kl_bmi_reset(struct ath6kl *ar)
{
	ar->bmi.done_sent = false;
}