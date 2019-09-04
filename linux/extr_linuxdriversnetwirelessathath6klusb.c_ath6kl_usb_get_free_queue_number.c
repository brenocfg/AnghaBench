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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ath6kl_usb {TYPE_1__* pipes; } ;
struct ath6kl {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  urb_cnt; } ;

/* Variables and functions */
 struct ath6kl_usb* ath6kl_usb_priv (struct ath6kl*) ; 

__attribute__((used)) static u16 ath6kl_usb_get_free_queue_number(struct ath6kl *ar, u8 pipe_id)
{
	struct ath6kl_usb *device = ath6kl_usb_priv(ar);

	return device->pipes[pipe_id].urb_cnt;
}