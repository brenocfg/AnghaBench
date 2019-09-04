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
typedef  scalar_t__ s64 ;

/* Variables and functions */
 scalar_t__ S64_MAX ; 
 scalar_t__ div64_s64 (unsigned int,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static s64 credits_from_len(unsigned int len, s64 slope, s64 port_rate)
{
	if (unlikely(port_rate == 0))
		return S64_MAX;

	return div64_s64(len * slope, port_rate);
}