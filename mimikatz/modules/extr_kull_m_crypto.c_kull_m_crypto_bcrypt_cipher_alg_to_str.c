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
 int /*<<< orphan*/ ** BCRYPT_CIPHER_ALGORITHMS ; 

PCWCHAR kull_m_crypto_bcrypt_cipher_alg_to_str(const DWORD alg)
{
	PCWCHAR result = NULL;
	if(alg && (alg <= ARRAYSIZE(BCRYPT_CIPHER_ALGORITHMS)))
		return BCRYPT_CIPHER_ALGORITHMS[alg - 1];
	return result;
}