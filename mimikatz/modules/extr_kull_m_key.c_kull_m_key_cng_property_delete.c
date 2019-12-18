#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* pProperty; struct TYPE_4__* pName; } ;
typedef  TYPE_1__* PKULL_M_KEY_CNG_PROPERTY ;

/* Variables and functions */
 int /*<<< orphan*/  LocalFree (TYPE_1__*) ; 

void kull_m_key_cng_property_delete(PKULL_M_KEY_CNG_PROPERTY property)
{
	if(property)
	{
		if(property->pName)
			LocalFree(property->pName);
		if(property->pProperty)
			LocalFree(property->pProperty);
		LocalFree(property);
	}
}