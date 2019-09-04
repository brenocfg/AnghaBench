#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct r8a66597 {TYPE_1__* pdata; } ;
struct TYPE_2__ {scalar_t__ on_chip; } ;

/* Variables and functions */
 unsigned short MBW_16 ; 
 unsigned short MBW_32 ; 

__attribute__((used)) static inline unsigned short mbw_value(struct r8a66597 *r8a66597)
{
	if (r8a66597->pdata->on_chip)
		return MBW_32;
	else
		return MBW_16;
}