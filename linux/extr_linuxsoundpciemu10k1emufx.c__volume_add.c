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
 int /*<<< orphan*/  CC_REG_NONZERO ; 
 int /*<<< orphan*/  C_00000000 ; 
 int /*<<< orphan*/  C_00000001 ; 
 int /*<<< orphan*/  C_00000002 ; 
 int /*<<< orphan*/  C_7fffffff ; 
 int /*<<< orphan*/  C_ffffffff ; 
 int /*<<< orphan*/  GPR_COND ; 
 int /*<<< orphan*/  OP (struct snd_emu10k1_fx8010_code*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iANDXOR ; 
 int /*<<< orphan*/  iMAC0 ; 
 int /*<<< orphan*/  iMACINT0 ; 
 int /*<<< orphan*/  iSKIP ; 

__attribute__((used)) static void _volume_add(struct snd_emu10k1_fx8010_code *icode, u32 *ptr, u32 dst, u32 src, u32 vol)
{
	OP(icode, ptr, iANDXOR, C_00000000, vol, C_ffffffff, C_7fffffff);
	OP(icode, ptr, iSKIP, GPR_COND, GPR_COND, CC_REG_NONZERO, C_00000002);
	OP(icode, ptr, iMACINT0, dst, dst, src, C_00000001);
	OP(icode, ptr, iSKIP, C_00000000, C_7fffffff, C_7fffffff, C_00000001);
	OP(icode, ptr, iMAC0, dst, dst, src, vol);
}