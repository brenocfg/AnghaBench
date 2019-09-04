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
struct slgt_info {int if_mode; int signals; } ;

/* Variables and functions */
 unsigned char BIT0 ; 
 unsigned char BIT1 ; 
 unsigned char BIT2 ; 
 unsigned char BIT3 ; 
 unsigned char BIT4 ; 
 unsigned char BIT5 ; 
 unsigned char BIT6 ; 
 unsigned char BIT7 ; 
 int MGSL_INTERFACE_LL ; 
 int MGSL_INTERFACE_MASK ; 
 int MGSL_INTERFACE_MSB_FIRST ; 
 int MGSL_INTERFACE_RL ; 
#define  MGSL_INTERFACE_RS232 130 
#define  MGSL_INTERFACE_RS422 129 
#define  MGSL_INTERFACE_V35 128 
 int SerialSignal_DTR ; 
 int SerialSignal_RTS ; 
 int /*<<< orphan*/  VCR ; 
 int /*<<< orphan*/  wr_reg8 (struct slgt_info*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void msc_set_vcr(struct slgt_info *info)
{
	unsigned char val = 0;

	/* VCR (V.24 control)
	 *
	 * 07..04  serial IF select
	 * 03      DTR
	 * 02      RTS
	 * 01      LL
	 * 00      RL
	 */

	switch(info->if_mode & MGSL_INTERFACE_MASK)
	{
	case MGSL_INTERFACE_RS232:
		val |= BIT5; /* 0010 */
		break;
	case MGSL_INTERFACE_V35:
		val |= BIT7 + BIT6 + BIT5; /* 1110 */
		break;
	case MGSL_INTERFACE_RS422:
		val |= BIT6; /* 0100 */
		break;
	}

	if (info->if_mode & MGSL_INTERFACE_MSB_FIRST)
		val |= BIT4;
	if (info->signals & SerialSignal_DTR)
		val |= BIT3;
	if (info->signals & SerialSignal_RTS)
		val |= BIT2;
	if (info->if_mode & MGSL_INTERFACE_LL)
		val |= BIT1;
	if (info->if_mode & MGSL_INTERFACE_RL)
		val |= BIT0;
	wr_reg8(info, VCR, val);
}