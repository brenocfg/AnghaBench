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
struct ewma_rssi {int dummy; } ;

/* Variables and functions */
 int DEFAULT_RSSI ; 
 unsigned long ewma_rssi_read (struct ewma_rssi*) ; 

__attribute__((used)) static inline int rt2x00link_get_avg_rssi(struct ewma_rssi *ewma)
{
	unsigned long avg;

	avg = ewma_rssi_read(ewma);
	if (avg)
		return -avg;

	return DEFAULT_RSSI;
}