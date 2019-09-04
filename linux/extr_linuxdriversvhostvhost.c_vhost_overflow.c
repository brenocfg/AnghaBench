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

/* Variables and functions */
 scalar_t__ ULONG_MAX ; 

__attribute__((used)) static bool vhost_overflow(u64 uaddr, u64 size)
{
	/* Make sure 64 bit math will not overflow. */
	return uaddr > ULONG_MAX || size > ULONG_MAX || uaddr > ULONG_MAX - size;
}