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
typedef  int u32 ;
struct net_device_stats {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  rx_crc_errors; } ;

/* Variables and functions */
 int ABORT ; 
 int COLON ; 
 int CRCOK ; 
 int LIMIT ; 
 int MIIER ; 
 int NIBON ; 
 int OVRUN ; 
 int SHORT ; 

__attribute__((used)) static inline int sis190_rx_pkt_err(u32 status, struct net_device_stats *stats)
{
#define ErrMask	(OVRUN | SHORT | LIMIT | MIIER | NIBON | COLON | ABORT)

	if ((status & CRCOK) && !(status & ErrMask))
		return 0;

	if (!(status & CRCOK))
		stats->rx_crc_errors++;
	else if (status & OVRUN)
		stats->rx_over_errors++;
	else if (status & (SHORT | LIMIT))
		stats->rx_length_errors++;
	else if (status & (MIIER | NIBON | COLON))
		stats->rx_frame_errors++;

	stats->rx_errors++;
	return -1;
}