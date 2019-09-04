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
struct adf7242_local {int dummy; } ;

/* Variables and functions */
 int STAT_RC_READY ; 
 int STAT_SPI_READY ; 
 int adf7242_wait_status (struct adf7242_local*,int,int,int) ; 

__attribute__((used)) static int adf7242_wait_rc_ready(struct adf7242_local *lp, int line)
{
	return adf7242_wait_status(lp, STAT_RC_READY | STAT_SPI_READY,
				   STAT_RC_READY | STAT_SPI_READY, line);
}