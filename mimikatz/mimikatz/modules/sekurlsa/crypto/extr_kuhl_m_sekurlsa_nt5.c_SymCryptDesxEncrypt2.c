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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {scalar_t__ outputWhitening; int /*<<< orphan*/  desKey; scalar_t__ inputWhitening; } ;
typedef  int* PULONGLONG ;
typedef  TYPE_1__* PCSYMCRYPT_NT5_DESX_EXPANDED_KEY ;
typedef  scalar_t__ PBYTE ;
typedef  scalar_t__ LPCBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  SymCryptDesGenCrypt2 (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

VOID SymCryptDesxEncrypt2(PCSYMCRYPT_NT5_DESX_EXPANDED_KEY pExpandedKey, LPCBYTE pbSrc, PBYTE pbDst)
{
	*(PULONGLONG) pbDst = *(PULONGLONG) pbSrc ^ *(PULONGLONG) pExpandedKey->inputWhitening;
	SymCryptDesGenCrypt2(&pExpandedKey->desKey, pbDst, pbDst, TRUE);
	*(PULONGLONG) pbDst ^= *(PULONGLONG) pExpandedKey->outputWhitening;
}