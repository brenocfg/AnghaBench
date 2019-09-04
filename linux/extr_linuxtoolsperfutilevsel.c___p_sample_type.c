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
 int /*<<< orphan*/  PERF_SAMPLE_ADDR ; 
 int /*<<< orphan*/  PERF_SAMPLE_BRANCH_STACK ; 
 int /*<<< orphan*/  PERF_SAMPLE_CALLCHAIN ; 
 int /*<<< orphan*/  PERF_SAMPLE_CPU ; 
 int /*<<< orphan*/  PERF_SAMPLE_DATA_SRC ; 
 int /*<<< orphan*/  PERF_SAMPLE_ID ; 
 int /*<<< orphan*/  PERF_SAMPLE_IDENTIFIER ; 
 int /*<<< orphan*/  PERF_SAMPLE_IP ; 
 int /*<<< orphan*/  PERF_SAMPLE_PERIOD ; 
 int /*<<< orphan*/  PERF_SAMPLE_PHYS_ADDR ; 
 int /*<<< orphan*/  PERF_SAMPLE_RAW ; 
 int /*<<< orphan*/  PERF_SAMPLE_READ ; 
 int /*<<< orphan*/  PERF_SAMPLE_REGS_INTR ; 
 int /*<<< orphan*/  PERF_SAMPLE_REGS_USER ; 
 int /*<<< orphan*/  PERF_SAMPLE_STACK_USER ; 
 int /*<<< orphan*/  PERF_SAMPLE_STREAM_ID ; 
 int /*<<< orphan*/  PERF_SAMPLE_TID ; 
 int /*<<< orphan*/  PERF_SAMPLE_TIME ; 
 int /*<<< orphan*/  PERF_SAMPLE_WEIGHT ; 
 int /*<<< orphan*/  __p_bits (char*,size_t,int /*<<< orphan*/ ,struct bit_names*) ; 

__attribute__((used)) static void __p_sample_type(char *buf, size_t size, u64 value)
{
#define bit_name(n) { PERF_SAMPLE_##n, #n }
	struct bit_names bits[] = {
		bit_name(IP), bit_name(TID), bit_name(TIME), bit_name(ADDR),
		bit_name(READ), bit_name(CALLCHAIN), bit_name(ID), bit_name(CPU),
		bit_name(PERIOD), bit_name(STREAM_ID), bit_name(RAW),
		bit_name(BRANCH_STACK), bit_name(REGS_USER), bit_name(STACK_USER),
		bit_name(IDENTIFIER), bit_name(REGS_INTR), bit_name(DATA_SRC),
		bit_name(WEIGHT), bit_name(PHYS_ADDR),
		{ .name = NULL, }
	};
#undef bit_name
	__p_bits(buf, size, value, bits);
}