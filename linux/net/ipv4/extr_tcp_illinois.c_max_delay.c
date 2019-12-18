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
struct illinois {scalar_t__ base_rtt; scalar_t__ max_rtt; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 max_delay(const struct illinois *ca)
{
	return ca->max_rtt - ca->base_rtt;
}