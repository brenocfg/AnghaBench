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

/* Variables and functions */
 scalar_t__ OSST_FIRST_SG ; 
 int ST_KILOBYTE ; 
 scalar_t__ max_dev ; 
 scalar_t__ max_sg_segs ; 
 int osst_buffer_size ; 
 scalar_t__ osst_max_dev ; 
 scalar_t__ osst_max_sg_segs ; 
 int osst_write_threshold ; 
 int write_threshold_kbs ; 

__attribute__((used)) static void validate_options (void)
{
  if (max_dev > 0)
		osst_max_dev = max_dev;  
  if (write_threshold_kbs > 0)
		osst_write_threshold = write_threshold_kbs * ST_KILOBYTE;
  if (osst_write_threshold > osst_buffer_size)
		osst_write_threshold = osst_buffer_size;
  if (max_sg_segs >= OSST_FIRST_SG)
		osst_max_sg_segs = max_sg_segs;
#if DEBUG
  printk(OSST_DEB_MSG "osst :D: max tapes %d, write threshold %d, max s/g segs %d.\n",
			   osst_max_dev, osst_write_threshold, osst_max_sg_segs);
#endif
}