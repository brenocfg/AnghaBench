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

__attribute__((used)) static inline uint64_t uint64_diff(uint64_t ts1, uint64_t ts2)
{
	return (ts1 < ts2) ?  (ts2 - ts1) : (ts1 - ts2);
}