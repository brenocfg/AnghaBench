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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 size_t BR_MCAST_DIR_RX ; 
 size_t BR_MCAST_DIR_TX ; 

__attribute__((used)) static void mcast_stats_add_dir(u64 *dst, u64 *src)
{
	dst[BR_MCAST_DIR_RX] += src[BR_MCAST_DIR_RX];
	dst[BR_MCAST_DIR_TX] += src[BR_MCAST_DIR_TX];
}