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
struct mite {scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ MITE_FCR (unsigned int) ; 
 unsigned int readl (scalar_t__) ; 

__attribute__((used)) static unsigned int mite_fifo_size(struct mite *mite, unsigned int channel)
{
	unsigned int fcr_bits = readl(mite->mmio + MITE_FCR(channel));
	unsigned int empty_count = (fcr_bits >> 16) & 0xff;
	unsigned int full_count = fcr_bits & 0xff;

	return empty_count + full_count;
}