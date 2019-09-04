#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned short base; scalar_t__ mode; } ;
typedef  TYPE_1__ imm_struct ;

/* Variables and functions */
 scalar_t__ IMM_EPP_16 ; 
 scalar_t__ IMM_EPP_32 ; 
 scalar_t__ IMM_EPP_8 ; 
 int imm_cpp (unsigned short,int) ; 

__attribute__((used)) static inline int imm_connect(imm_struct *dev, int flag)
{
	unsigned short ppb = dev->base;

	imm_cpp(ppb, 0xe0);	/* Select device 0 in compatible mode */
	imm_cpp(ppb, 0x30);	/* Disconnect all devices */

	if ((dev->mode == IMM_EPP_8) ||
	    (dev->mode == IMM_EPP_16) ||
	    (dev->mode == IMM_EPP_32))
		return imm_cpp(ppb, 0x28);	/* Select device 0 in EPP mode */
	return imm_cpp(ppb, 0xe0);	/* Select device 0 in compatible mode */
}