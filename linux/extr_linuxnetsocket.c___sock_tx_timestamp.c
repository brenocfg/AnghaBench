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
typedef  int /*<<< orphan*/  __u8 ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  SKBTX_HW_TSTAMP ; 
 int /*<<< orphan*/  SKBTX_SCHED_TSTAMP ; 
 int /*<<< orphan*/  SKBTX_SW_TSTAMP ; 
 int SOF_TIMESTAMPING_TX_HARDWARE ; 
 int SOF_TIMESTAMPING_TX_SCHED ; 
 int SOF_TIMESTAMPING_TX_SOFTWARE ; 

void __sock_tx_timestamp(__u16 tsflags, __u8 *tx_flags)
{
	u8 flags = *tx_flags;

	if (tsflags & SOF_TIMESTAMPING_TX_HARDWARE)
		flags |= SKBTX_HW_TSTAMP;

	if (tsflags & SOF_TIMESTAMPING_TX_SOFTWARE)
		flags |= SKBTX_SW_TSTAMP;

	if (tsflags & SOF_TIMESTAMPING_TX_SCHED)
		flags |= SKBTX_SCHED_TSTAMP;

	*tx_flags = flags;
}