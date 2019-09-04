#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct htc_target {TYPE_3__* dev; } ;
struct TYPE_6__ {TYPE_2__* ar; } ;
struct TYPE_5__ {TYPE_1__* htc_ops; } ;
struct TYPE_4__ {void (* flush_rx_buf ) (struct htc_target*) ;} ;

/* Variables and functions */
 void stub1 (struct htc_target*) ; 

__attribute__((used)) static inline void ath6kl_htc_flush_rx_buf(struct htc_target *target)
{
	return target->dev->ar->htc_ops->flush_rx_buf(target);
}