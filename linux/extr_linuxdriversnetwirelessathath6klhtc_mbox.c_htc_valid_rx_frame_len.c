#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct htc_target {TYPE_2__* dev; } ;
typedef  enum htc_endpoint_id { ____Placeholder_htc_endpoint_id } htc_endpoint_id ;
struct TYPE_4__ {TYPE_1__* ar; } ;
struct TYPE_3__ {int ctrl_ep; } ;

/* Variables and functions */
 int ATH6KL_AMSDU_BUFFER_SIZE ; 
 int ATH6KL_BUFFER_SIZE ; 

__attribute__((used)) static inline bool htc_valid_rx_frame_len(struct htc_target *target,
					  enum htc_endpoint_id eid, int len)
{
	return (eid == target->dev->ar->ctrl_ep) ?
		len <= ATH6KL_BUFFER_SIZE : len <= ATH6KL_AMSDU_BUFFER_SIZE;
}