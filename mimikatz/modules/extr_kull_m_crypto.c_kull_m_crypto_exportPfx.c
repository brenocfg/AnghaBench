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
struct TYPE_3__ {int /*<<< orphan*/ * pbData; int /*<<< orphan*/  cbData; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HCERTSTORE ;
typedef  TYPE_1__ CRYPT_DATA_BLOB ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int EXPORT_PRIVATE_KEYS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MIMIKATZ ; 
 scalar_t__ PFXExportCertStoreEx (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int REPORT_NOT_ABLE_TO_EXPORT_PRIVATE_KEY ; 
 int /*<<< orphan*/  kull_m_file_writeData (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

BOOL kull_m_crypto_exportPfx(HCERTSTORE hStore, LPCWSTR filename)
{
	BOOL isExported = FALSE;
	CRYPT_DATA_BLOB bDataBlob = {0, NULL};
	if(PFXExportCertStoreEx(hStore, &bDataBlob, MIMIKATZ, NULL, EXPORT_PRIVATE_KEYS | REPORT_NOT_ABLE_TO_EXPORT_PRIVATE_KEY))
	{
		if(bDataBlob.pbData = (BYTE *) LocalAlloc(LPTR, bDataBlob.cbData))
		{
			if(PFXExportCertStoreEx(hStore, &bDataBlob, MIMIKATZ, NULL, EXPORT_PRIVATE_KEYS | REPORT_NOT_ABLE_TO_EXPORT_PRIVATE_KEY))
				isExported = kull_m_file_writeData(filename, bDataBlob.pbData, bDataBlob.cbData);
			LocalFree(bDataBlob.pbData);
		}
	}
	if(!isExported)
		PRINT_ERROR_AUTO(L"PFXExportCertStoreEx");
	return isExported;
}