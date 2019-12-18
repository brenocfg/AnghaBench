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
typedef  int /*<<< orphan*/ * PCWCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 int const ARRAYSIZE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** BCRYPT_INTERFACES ; 

PCWCHAR kull_m_crypto_bcrypt_interface_to_str(const DWORD interf)
{
	PCWCHAR result = NULL;
	if(interf && (interf <= ARRAYSIZE(BCRYPT_INTERFACES)))
		return BCRYPT_INTERFACES[interf - 1];
	return result;
}