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
struct TYPE_3__ {int /*<<< orphan*/  id; scalar_t__ name; } ;
typedef  scalar_t__ PCWSTR ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  ALG_ID ;

/* Variables and functions */
 size_t ARRAYSIZE (TYPE_1__*) ; 
 scalar_t__ _wcsicmp (scalar_t__,scalar_t__) ; 
 TYPE_1__* kull_m_crypto_calgid ; 

ALG_ID kull_m_crypto_name_to_algid(PCWSTR name)
{
	DWORD i;
	if(name)
		for(i = 0; i < ARRAYSIZE(kull_m_crypto_calgid); i++)
			if((_wcsicmp(name, kull_m_crypto_calgid[i].name) == 0) || (_wcsicmp(name, kull_m_crypto_calgid[i].name + 5) == 0))
				return kull_m_crypto_calgid[i].id;
	return 0;
}