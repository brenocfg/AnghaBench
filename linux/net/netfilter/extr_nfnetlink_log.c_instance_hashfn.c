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
typedef  int u_int8_t ;
typedef  int u_int16_t ;

/* Variables and functions */
 int INSTANCE_BUCKETS ; 

__attribute__((used)) static inline u_int8_t instance_hashfn(u_int16_t group_num)
{
	return ((group_num & 0xff) % INSTANCE_BUCKETS);
}