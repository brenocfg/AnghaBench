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
struct bit_names {char* member_1; int /*<<< orphan*/ * name; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_SAMPLE_BRANCH_ABORT_TX ; 
 int /*<<< orphan*/  PERF_SAMPLE_BRANCH_ANY ; 
 int /*<<< orphan*/  PERF_SAMPLE_BRANCH_ANY_CALL ; 
 int /*<<< orphan*/  PERF_SAMPLE_BRANCH_ANY_RETURN ; 
 int /*<<< orphan*/  PERF_SAMPLE_BRANCH_CALL ; 
 int /*<<< orphan*/  PERF_SAMPLE_BRANCH_CALL_STACK ; 
 int /*<<< orphan*/  PERF_SAMPLE_BRANCH_COND ; 
 int /*<<< orphan*/  PERF_SAMPLE_BRANCH_HV ; 
 int /*<<< orphan*/  PERF_SAMPLE_BRANCH_IND_CALL ; 
 int /*<<< orphan*/  PERF_SAMPLE_BRANCH_IND_JUMP ; 
 int /*<<< orphan*/  PERF_SAMPLE_BRANCH_IN_TX ; 
 int /*<<< orphan*/  PERF_SAMPLE_BRANCH_KERNEL ; 
 int /*<<< orphan*/  PERF_SAMPLE_BRANCH_NO_CYCLES ; 
 int /*<<< orphan*/  PERF_SAMPLE_BRANCH_NO_FLAGS ; 
 int /*<<< orphan*/  PERF_SAMPLE_BRANCH_NO_TX ; 
 int /*<<< orphan*/  PERF_SAMPLE_BRANCH_USER ; 
 int /*<<< orphan*/  __p_bits (char*,size_t,int /*<<< orphan*/ ,struct bit_names*) ; 

__attribute__((used)) static void __p_branch_sample_type(char *buf, size_t size, u64 value)
{
#define bit_name(n) { PERF_SAMPLE_BRANCH_##n, #n }
	struct bit_names bits[] = {
		bit_name(USER), bit_name(KERNEL), bit_name(HV), bit_name(ANY),
		bit_name(ANY_CALL), bit_name(ANY_RETURN), bit_name(IND_CALL),
		bit_name(ABORT_TX), bit_name(IN_TX), bit_name(NO_TX),
		bit_name(COND), bit_name(CALL_STACK), bit_name(IND_JUMP),
		bit_name(CALL), bit_name(NO_FLAGS), bit_name(NO_CYCLES),
		{ .name = NULL, }
	};
#undef bit_name
	__p_bits(buf, size, value, bits);
}