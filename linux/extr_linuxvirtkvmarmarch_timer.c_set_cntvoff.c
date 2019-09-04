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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  __kvm_timer_set_cntvoff ; 
 int /*<<< orphan*/  kvm_call_hyp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_cntvoff(u64 cntvoff)
{
	u32 low = lower_32_bits(cntvoff);
	u32 high = upper_32_bits(cntvoff);

	/*
	 * Since kvm_call_hyp doesn't fully support the ARM PCS especially on
	 * 32-bit systems, but rather passes register by register shifted one
	 * place (we put the function address in r0/x0), we cannot simply pass
	 * a 64-bit value as an argument, but have to split the value in two
	 * 32-bit halves.
	 */
	kvm_call_hyp(__kvm_timer_set_cntvoff, low, high);
}