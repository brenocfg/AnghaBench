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
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  neo2200_sync (struct fb_info*) ; 

__attribute__((used)) static inline void neo2200_wait_fifo(struct fb_info *info,
				     int requested_fifo_space)
{
	//  ndev->neo.waitfifo_calls++;
	//  ndev->neo.waitfifo_sum += requested_fifo_space;

	/* FIXME: does not work
	   if (neo_fifo_space < requested_fifo_space)
	   {
	   neo_fifo_waitcycles++;

	   while (1)
	   {
	   neo_fifo_space = (neo2200->bltStat >> 8);
	   if (neo_fifo_space >= requested_fifo_space)
	   break;
	   }
	   }
	   else
	   {
	   neo_fifo_cache_hits++;
	   }

	   neo_fifo_space -= requested_fifo_space;
	 */

	neo2200_sync(info);
}