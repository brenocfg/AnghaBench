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
struct bpf_reg_state {scalar_t__ smin_value; scalar_t__ smax_value; } ;
typedef  scalar_t__ s64 ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ S32_MAX ; 
 scalar_t__ S32_MIN ; 

__attribute__((used)) static bool cmp_val_with_extended_s64(s64 sval, struct bpf_reg_state *reg)
{
	return ((s32)sval >= 0 &&
		reg->smin_value >= 0 && reg->smax_value <= S32_MAX) ||
	       ((s32)sval < 0 &&
		reg->smax_value <= 0 && reg->smin_value >= S32_MIN);
}