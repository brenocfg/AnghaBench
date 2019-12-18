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
struct snd_emu10k1_fx8010_code {int dummy; } ;

/* Variables and functions */
 int A_C_00000000 ; 
 int A_C_00010000 ; 
 int A_C_80000000 ; 
 int A_C_ffffffff ; 
 int A_GPR (int) ; 
 int /*<<< orphan*/  A_OP (struct snd_emu10k1_fx8010_code*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  iACC3 ; 
 int /*<<< orphan*/  iANDXOR ; 
 int /*<<< orphan*/  iMACINT0 ; 
 int /*<<< orphan*/  iTSTNEG ; 

__attribute__((used)) static int snd_emu10k1_audigy_dsp_convert_32_to_2x16(
				struct snd_emu10k1_fx8010_code *icode,
				u32 *ptr, int tmp, int bit_shifter16,
				int reg_in, int reg_out)
{
	A_OP(icode, ptr, iACC3, A_GPR(tmp + 1), reg_in, A_C_00000000, A_C_00000000);
	A_OP(icode, ptr, iANDXOR, A_GPR(tmp), A_GPR(tmp + 1), A_GPR(bit_shifter16 - 1), A_C_00000000);
	A_OP(icode, ptr, iTSTNEG, A_GPR(tmp + 2), A_GPR(tmp), A_C_80000000, A_GPR(bit_shifter16 - 2));
	A_OP(icode, ptr, iANDXOR, A_GPR(tmp + 2), A_GPR(tmp + 2), A_C_80000000, A_C_00000000);
	A_OP(icode, ptr, iANDXOR, A_GPR(tmp), A_GPR(tmp), A_GPR(bit_shifter16 - 3), A_C_00000000);
	A_OP(icode, ptr, iMACINT0, A_GPR(tmp), A_C_00000000, A_GPR(tmp), A_C_00010000);
	A_OP(icode, ptr, iANDXOR, reg_out, A_GPR(tmp), A_C_ffffffff, A_GPR(tmp + 2));
	A_OP(icode, ptr, iACC3, reg_out + 1, A_GPR(tmp + 1), A_C_00000000, A_C_00000000);
	return 1;
}