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
typedef  int u16 ;
struct fcoe_fcf {int flags; } ;

/* Variables and functions */
 int FIP_FL_AVAIL ; 
 int FIP_FL_SOL ; 

__attribute__((used)) static inline int fcoe_ctlr_fcf_usable(struct fcoe_fcf *fcf)
{
	u16 flags = FIP_FL_SOL | FIP_FL_AVAIL;

	return (fcf->flags & flags) == flags;
}