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
 int /*<<< orphan*/  PERF_FORMAT_GROUP ; 
 int /*<<< orphan*/  PERF_FORMAT_ID ; 
 int /*<<< orphan*/  PERF_FORMAT_TOTAL_TIME_ENABLED ; 
 int /*<<< orphan*/  PERF_FORMAT_TOTAL_TIME_RUNNING ; 
 int /*<<< orphan*/  __p_bits (char*,size_t,int /*<<< orphan*/ ,struct bit_names*) ; 

__attribute__((used)) static void __p_read_format(char *buf, size_t size, u64 value)
{
#define bit_name(n) { PERF_FORMAT_##n, #n }
	struct bit_names bits[] = {
		bit_name(TOTAL_TIME_ENABLED), bit_name(TOTAL_TIME_RUNNING),
		bit_name(ID), bit_name(GROUP),
		{ .name = NULL, }
	};
#undef bit_name
	__p_bits(buf, size, value, bits);
}