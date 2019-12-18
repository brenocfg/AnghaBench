#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_4__ {TYPE_1__ v4; } ;
struct cidr {TYPE_2__ addr; } ;

/* Variables and functions */
 int ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ printed ; 
 int /*<<< orphan*/  qprintf (char*) ; 

__attribute__((used)) static bool cidr_private4(struct cidr *a)
{
	uint32_t x = ntohl(a->addr.v4.s_addr);

	if (printed)
		qprintf(" ");

	if (((x >= 0x0A000000) && (x <= 0x0AFFFFFF)) ||
	    ((x >= 0xAC100000) && (x <= 0xAC1FFFFF)) ||
	    ((x >= 0xC0A80000) && (x <= 0xC0A8FFFF)))
	{
		qprintf("1");
		return true;
	}
	else
	{
		qprintf("0");
		return false;
	}
}