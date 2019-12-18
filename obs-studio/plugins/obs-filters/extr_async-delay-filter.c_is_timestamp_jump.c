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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ SEC_TO_NSEC ; 

__attribute__((used)) static inline bool is_timestamp_jump(uint64_t ts, uint64_t prev_ts)
{
	return ts < prev_ts || (ts - prev_ts) > SEC_TO_NSEC;
}