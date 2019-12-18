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
 int U32_MAX ; 
 int XT_HASHLIMIT_BYTE_SHIFT ; 

__attribute__((used)) static u64 user2rate_bytes(u32 user)
{
	u64 r;

	r = user ? U32_MAX / user : U32_MAX;
	return (r - 1) << XT_HASHLIMIT_BYTE_SHIFT;
}