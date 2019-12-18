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
struct rme96 {int wcreg; } ;

/* Variables and functions */
 int RME96_WCR_BITPOS_MONITOR_0 ; 
 int RME96_WCR_BITPOS_MONITOR_1 ; 

__attribute__((used)) static int
snd_rme96_getmontracks(struct rme96 *rme96)
{
	return ((rme96->wcreg >> RME96_WCR_BITPOS_MONITOR_0) & 1) +
		(((rme96->wcreg >> RME96_WCR_BITPOS_MONITOR_1) & 1) << 1);
}