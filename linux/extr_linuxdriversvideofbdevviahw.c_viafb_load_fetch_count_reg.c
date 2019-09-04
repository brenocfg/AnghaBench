#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct io_register {int dummy; } ;
struct TYPE_4__ {int reg_num; struct io_register* reg; } ;
struct TYPE_5__ {int reg_num; struct io_register* reg; } ;
struct TYPE_6__ {TYPE_1__ iga2_fetch_count_reg; TYPE_2__ iga1_fetch_count_reg; } ;

/* Variables and functions */
#define  IGA1 129 
 int IGA1_FETCH_COUNT_FORMULA (int,int) ; 
#define  IGA2 128 
 int IGA2_FETCH_COUNT_FORMULA (int,int) ; 
 int /*<<< orphan*/  VIACR ; 
 int /*<<< orphan*/  VIASR ; 
 TYPE_3__ fetch_count_reg ; 
 int /*<<< orphan*/  viafb_load_reg (int,int,struct io_register*,int /*<<< orphan*/ ) ; 

void viafb_load_fetch_count_reg(int h_addr, int bpp_byte, int set_iga)
{
	int reg_value;
	int viafb_load_reg_num;
	struct io_register *reg = NULL;

	switch (set_iga) {
	case IGA1:
		reg_value = IGA1_FETCH_COUNT_FORMULA(h_addr, bpp_byte);
		viafb_load_reg_num = fetch_count_reg.
			iga1_fetch_count_reg.reg_num;
		reg = fetch_count_reg.iga1_fetch_count_reg.reg;
		viafb_load_reg(reg_value, viafb_load_reg_num, reg, VIASR);
		break;
	case IGA2:
		reg_value = IGA2_FETCH_COUNT_FORMULA(h_addr, bpp_byte);
		viafb_load_reg_num = fetch_count_reg.
			iga2_fetch_count_reg.reg_num;
		reg = fetch_count_reg.iga2_fetch_count_reg.reg;
		viafb_load_reg(reg_value, viafb_load_reg_num, reg, VIACR);
		break;
	}

}