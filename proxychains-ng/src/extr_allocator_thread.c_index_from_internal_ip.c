#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int* octet; } ;
typedef  TYPE_1__ ip_type4 ;

/* Variables and functions */
 int /*<<< orphan*/  PFUNC () ; 

uint32_t index_from_internal_ip(ip_type4 internalip) {
	PFUNC();
	ip_type4 tmp = internalip;
	uint32_t ret;
	ret = tmp.octet[3] + (tmp.octet[2] << 8) + (tmp.octet[1] << 16);
	ret -= 1;
	return ret;
}