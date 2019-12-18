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
typedef  int /*<<< orphan*/  PKULL_M_KEY_CNG_PROPERTY ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_key_cng_property_delete (int /*<<< orphan*/ ) ; 

void kull_m_key_cng_properties_delete(PKULL_M_KEY_CNG_PROPERTY *properties, DWORD count)
{
	DWORD i;
	if(properties)
	{
		for(i = 0; i < count; i++)
			kull_m_key_cng_property_delete(properties[i]);
		LocalFree(properties);
	}
}