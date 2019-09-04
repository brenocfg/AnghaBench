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
struct slgt_info {int signals; } ;

/* Variables and functions */
 unsigned short BIT0 ; 
 unsigned short BIT1 ; 
 unsigned short BIT2 ; 
 unsigned short BIT3 ; 
 int /*<<< orphan*/  SSR ; 
 int SerialSignal_CTS ; 
 int SerialSignal_DCD ; 
 int SerialSignal_DSR ; 
 int SerialSignal_DTR ; 
 int SerialSignal_RI ; 
 int SerialSignal_RTS ; 
 unsigned short rd_reg16 (struct slgt_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_signals(struct slgt_info *info)
{
	unsigned short status = rd_reg16(info, SSR);

	/* clear all serial signals except RTS and DTR */
	info->signals &= SerialSignal_RTS | SerialSignal_DTR;

	if (status & BIT3)
		info->signals |= SerialSignal_DSR;
	if (status & BIT2)
		info->signals |= SerialSignal_CTS;
	if (status & BIT1)
		info->signals |= SerialSignal_DCD;
	if (status & BIT0)
		info->signals |= SerialSignal_RI;
}