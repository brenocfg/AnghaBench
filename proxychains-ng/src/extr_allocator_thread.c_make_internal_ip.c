#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {int* octet; } ;
typedef  TYPE_2__ ip_type4 ;
struct TYPE_5__ {TYPE_2__ v4; } ;
struct TYPE_7__ {TYPE_1__ addr; } ;

/* Variables and functions */
 TYPE_4__ ip_type_invalid ; 
 int remote_dns_subnet ; 

ip_type4 make_internal_ip(uint32_t index) {
	ip_type4 ret;
	index++; // so we can start at .0.0.1
	if(index > 0xFFFFFF)
		return ip_type_invalid.addr.v4;
	ret.octet[0] = remote_dns_subnet & 0xFF;
	ret.octet[1] = (index & 0xFF0000) >> 16;
	ret.octet[2] = (index & 0xFF00) >> 8;
	ret.octet[3] = index & 0xFF;
	return ret;
}