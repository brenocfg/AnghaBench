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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int CREDITS_PER_JIFFY_BYTES ; 
 int HZ ; 

__attribute__((used)) static u32 user2credits_byte(u32 user)
{
	u64 us = user;
	us *= HZ * CREDITS_PER_JIFFY_BYTES;
	return (u32) (us >> 32);
}