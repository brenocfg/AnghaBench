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
struct TYPE_3__ {size_t const id; char* name; } ;
typedef  char* PCWSTR ;
typedef  size_t DWORD ;

/* Variables and functions */
 size_t ARRAYSIZE (TYPE_1__*) ; 
 TYPE_1__* kull_m_crypto_provider_types ; 

PCWSTR kull_m_crypto_provider_type_to_name(const DWORD dwProvType)
{
	DWORD i;
	if(!dwProvType)
		return L"PROV_cng" + 5;
	for(i = 0; i < ARRAYSIZE(kull_m_crypto_provider_types); i++)
		if(kull_m_crypto_provider_types[i].id == dwProvType)
			return kull_m_crypto_provider_types[i].name + 5;
	return NULL;
}