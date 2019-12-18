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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */

__attribute__((used)) static int64_t _sort__addr_cmp(u64 left_ip, u64 right_ip)
{
	return (int64_t)(right_ip - left_ip);
}