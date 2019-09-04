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
typedef  int /*<<< orphan*/  u32 ;
struct r8152 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMC_FCR_MCU_EN ; 
 int /*<<< orphan*/  MCU_TYPE_PLA ; 
 int /*<<< orphan*/  PLA_FMC ; 
 int /*<<< orphan*/  ocp_read_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocp_write_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r8152b_reset_packet_filter(struct r8152 *tp)
{
	u32	ocp_data;

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_FMC);
	ocp_data &= ~FMC_FCR_MCU_EN;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_FMC, ocp_data);
	ocp_data |= FMC_FCR_MCU_EN;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_FMC, ocp_data);
}