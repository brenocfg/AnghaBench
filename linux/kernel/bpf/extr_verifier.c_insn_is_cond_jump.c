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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ BPF_CALL ; 
 scalar_t__ BPF_CLASS (scalar_t__) ; 
 scalar_t__ BPF_EXIT ; 
 scalar_t__ BPF_JA ; 
 scalar_t__ BPF_JMP ; 
 scalar_t__ BPF_JMP32 ; 
 scalar_t__ BPF_OP (scalar_t__) ; 

__attribute__((used)) static bool insn_is_cond_jump(u8 code)
{
	u8 op;

	if (BPF_CLASS(code) == BPF_JMP32)
		return true;

	if (BPF_CLASS(code) != BPF_JMP)
		return false;

	op = BPF_OP(code);
	return op != BPF_JA && op != BPF_EXIT && op != BPF_CALL;
}