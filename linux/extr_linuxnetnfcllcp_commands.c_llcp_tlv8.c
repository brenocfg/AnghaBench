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
typedef  size_t u8 ;

/* Variables and functions */
 size_t* llcp_tlv_length ; 

__attribute__((used)) static u8 llcp_tlv8(u8 *tlv, u8 type)
{
	if (tlv[0] != type || tlv[1] != llcp_tlv_length[tlv[0]])
		return 0;

	return tlv[2];
}