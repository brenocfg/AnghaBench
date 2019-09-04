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
typedef  scalar_t__ uint32_t ;
struct hvc_iucv_private {int dummy; } ;

/* Variables and functions */
 scalar_t__ HVC_IUCV_MAGIC ; 
 scalar_t__ hvc_iucv_devices ; 
 struct hvc_iucv_private** hvc_iucv_table ; 

__attribute__((used)) static struct hvc_iucv_private *hvc_iucv_get_private(uint32_t num)
{
	if ((num < HVC_IUCV_MAGIC) || (num - HVC_IUCV_MAGIC > hvc_iucv_devices))
		return NULL;
	return hvc_iucv_table[num - HVC_IUCV_MAGIC];
}