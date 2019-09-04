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
struct efx_channel {TYPE_1__* type; } ;
struct TYPE_2__ {scalar_t__ (* want_txqs ) (struct efx_channel*) ;} ;

/* Variables and functions */
 scalar_t__ stub1 (struct efx_channel*) ; 

__attribute__((used)) static inline bool efx_channel_has_tx_queues(struct efx_channel *channel)
{
	return channel->type && channel->type->want_txqs &&
				channel->type->want_txqs(channel);
}