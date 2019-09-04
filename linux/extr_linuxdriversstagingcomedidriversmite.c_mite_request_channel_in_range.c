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
struct mite_ring {int dummy; } ;
struct mite_channel {int dummy; } ;
struct mite {int dummy; } ;

/* Variables and functions */
 struct mite_channel* __mite_request_channel (struct mite*,struct mite_ring*,unsigned int,unsigned int) ; 

struct mite_channel *mite_request_channel_in_range(struct mite *mite,
						   struct mite_ring *ring,
						   unsigned int min_channel,
						   unsigned int max_channel)
{
	return __mite_request_channel(mite, ring, min_channel, max_channel);
}