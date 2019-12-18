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
typedef  int st32 ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
#define  E_MAGIC 138 
#define  I_MAGIC 137 
#define  K_MAGIC 136 
#define  M_MAGIC 135 
#define  N_MAGIC 134 
#define  P_MAGIC 133 
#define  Q_MAGIC 132 
 int R_ASM_ARCH_ARM ; 
 int R_ASM_ARCH_MIPS ; 
 int R_ASM_ARCH_PPC ; 
 int R_ASM_ARCH_SPARC ; 
 int R_ASM_ARCH_X86 ; 
#define  S_MAGIC 131 
#define  T_MAGIC 130 
#define  U_MAGIC 129 
#define  V_MAGIC 128 
 int /*<<< orphan*/  r_buf_read_be32_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int r_bin_p9_get_arch(RBuffer *b, int *bits, int *big_endian) {
	st32 a = (st32) r_buf_read_be32_at (b, 0);
	if (bits) {
		*bits = 32;
	}
	if (big_endian) {
		*big_endian = 0;
	}
	switch (a) {
	case I_MAGIC:
		return R_ASM_ARCH_X86;
	case T_MAGIC:
		if (bits) {
			*bits = 64;
		}
		return R_ASM_ARCH_PPC;
	case S_MAGIC:
		if (bits) {
			*bits = 64;
		}
		return R_ASM_ARCH_X86;
	case K_MAGIC:
		return R_ASM_ARCH_SPARC;
	case U_MAGIC:
		if (bits) {
			*bits = 64;
		}
		return R_ASM_ARCH_SPARC;
	case V_MAGIC:
	case M_MAGIC:
	case N_MAGIC:
	case P_MAGIC:
		return R_ASM_ARCH_MIPS;
	case E_MAGIC:
		return R_ASM_ARCH_ARM;
	case Q_MAGIC:
		return R_ASM_ARCH_PPC;
	//case A_MAGIC: // 68020
	}
	return 0;
}