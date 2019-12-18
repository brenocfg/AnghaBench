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
typedef  scalar_t__ PKULL_M_DPAPI_MASTERKEY_CREDHIST ;

/* Variables and functions */
 int /*<<< orphan*/  LocalFree (scalar_t__) ; 

void kull_m_dpapi_masterkeys_credhist_delete(PKULL_M_DPAPI_MASTERKEY_CREDHIST credhist)
{
	if(credhist)
		LocalFree(credhist);
}