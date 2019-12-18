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
typedef  scalar_t__ LPSTR ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CryptSetProvParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  PP_KEYEXCHANGE_PIN ; 
 int /*<<< orphan*/  PP_SIGNATURE_PIN ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 scalar_t__ TRUE ; 

BOOL makePin(HCRYPTPROV hProv, BOOL isHw, LPSTR pin)
{
	BOOL status = FALSE;
	if(isHw && pin)
	{
		if(!(status = CryptSetProvParam(hProv, PP_KEYEXCHANGE_PIN, (const BYTE *) pin, 0)))
		{
			PRINT_ERROR_AUTO(L"CryptSetProvParam(PP_KEYEXCHANGE_PIN)");
			if(!(status = CryptSetProvParam(hProv, PP_SIGNATURE_PIN, (const BYTE *) pin, 0)))
				PRINT_ERROR_AUTO(L"CryptSetProvParam(PP_SIGNATURE_PIN)");
		}
	}
	else status = TRUE;
	return status;
}