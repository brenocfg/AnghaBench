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
typedef  scalar_t__ u32 ;
struct htcp {scalar_t__ last_cong; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 

__attribute__((used)) static inline u32 htcp_cong_time(const struct htcp *ca)
{
	return jiffies - ca->last_cong;
}