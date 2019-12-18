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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 size_t nla_total_size (int) ; 

__attribute__((used)) static size_t j1939_sk_opt_stats_get_size(void)
{
	return
		nla_total_size(sizeof(u32)) + /* J1939_NLA_BYTES_ACKED */
		0;
}