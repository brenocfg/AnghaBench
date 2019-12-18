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
 int /*<<< orphan*/ ** KP_MODE_DESCR ; 

PCWCHAR kull_m_crypto_kp_mode_to_str(const DWORD keyMode)
{
	PCWCHAR result = NULL;
	if(keyMode && (keyMode <= ARRAYSIZE(KP_MODE_DESCR)))
		return KP_MODE_DESCR[keyMode - 1];
	return result;
}