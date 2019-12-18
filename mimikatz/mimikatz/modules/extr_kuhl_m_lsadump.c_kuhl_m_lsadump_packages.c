#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  size_t ULONG ;
struct TYPE_10__ {size_t fCapabilities; int /*<<< orphan*/  Name; int /*<<< orphan*/  wVersion; int /*<<< orphan*/  wRPCID; int /*<<< orphan*/  cbMaxToken; int /*<<< orphan*/  Comment; } ;
struct TYPE_9__ {TYPE_3__* pvBuffer; int /*<<< orphan*/  cbBuffer; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {int member_1; TYPE_2__* member_2; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ SecBufferDesc ;
typedef  TYPE_2__ SecBuffer ;
typedef  scalar_t__ SECURITY_STATUS ;
typedef  TYPE_3__* PSecPkgInfo ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  CtxtHandle ;
typedef  int /*<<< orphan*/  CredHandle ;

/* Variables and functions */
 size_t ARRAYSIZE (char**) ; 
 scalar_t__ AcquireCredentialsHandle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteSecurityContext (int /*<<< orphan*/ *) ; 
 scalar_t__ EnumerateSecurityPackages (size_t*,TYPE_3__**) ; 
 int /*<<< orphan*/  FreeContextBuffer (TYPE_3__*) ; 
 int /*<<< orphan*/  FreeCredentialHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISC_REQ_ALLOCATE_MEMORY ; 
 scalar_t__ InitializeSecurityContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,size_t*,int /*<<< orphan*/ *) ; 
 char** PACKAGES_FLAGS ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,scalar_t__) ; 
 int /*<<< orphan*/  SECBUFFER_TOKEN ; 
 int /*<<< orphan*/  SECBUFFER_VERSION ; 
 int /*<<< orphan*/  SECPKG_CRED_OUTBOUND ; 
 int /*<<< orphan*/  SECURITY_NATIVE_DREP ; 
 scalar_t__ SEC_E_INCOMPLETE_MESSAGE ; 
 scalar_t__ SEC_E_OK ; 
 scalar_t__ SEC_I_COMPLETE_AND_CONTINUE ; 
 scalar_t__ SEC_I_COMPLETE_NEEDED ; 
 scalar_t__ SEC_I_CONTINUE_NEEDED ; 
 scalar_t__ SEC_I_INCOMPLETE_CREDENTIALS ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

NTSTATUS kuhl_m_lsadump_packages(int argc, wchar_t * argv[])
{
	SECURITY_STATUS status;
	ULONG cPackages, i, j;
	PSecPkgInfo pPackageInfo;
	CredHandle hCred;
	CtxtHandle hCtx;
	SecBuffer OutBuff = {0, SECBUFFER_TOKEN, NULL};
	SecBufferDesc Output = {SECBUFFER_VERSION, 1, &OutBuff};
	ULONG ContextAttr;

	status = EnumerateSecurityPackages(&cPackages, &pPackageInfo);
	if(status == SEC_E_OK)
	{
		for(i = 0; i < cPackages; i++)
		{
			kprintf(L"Name        : %s\nDescription : %s\nCapabilities: %08x ( ", pPackageInfo[i].Name, pPackageInfo[i].Comment, pPackageInfo[i].fCapabilities);
			for(j = 0; j < sizeof(ULONG) * 8; j++)
				if((pPackageInfo[i].fCapabilities >> j) & 1)
					kprintf(L"%s ; ", (j < ARRAYSIZE(PACKAGES_FLAGS)) ? PACKAGES_FLAGS[j] : L"?");
			kprintf(L")\nMaxToken    : %u\nRPCID       : 0x%04x (%hu)\nVersion     : %hu\n", pPackageInfo[i].cbMaxToken, pPackageInfo[i].wRPCID, pPackageInfo[i].wRPCID, pPackageInfo[i].wVersion);

			if(argc)
			{
				status = AcquireCredentialsHandle(NULL, pPackageInfo[i].Name, SECPKG_CRED_OUTBOUND, NULL, NULL, NULL, NULL, &hCred, NULL);
				if(status == SEC_E_OK)
				{
					status = InitializeSecurityContext(&hCred, NULL, argv[0], ISC_REQ_ALLOCATE_MEMORY, 0, SECURITY_NATIVE_DREP, NULL, 0, &hCtx, &Output, &ContextAttr, NULL);
					if((status == SEC_E_OK) || (status == SEC_I_COMPLETE_AND_CONTINUE)  || (status == SEC_I_COMPLETE_NEEDED)  || (status == SEC_I_CONTINUE_NEEDED)  || (status == SEC_I_INCOMPLETE_CREDENTIALS)  || (status == SEC_E_INCOMPLETE_MESSAGE))
					{
						kull_m_string_wprintf_hex(OutBuff.pvBuffer, OutBuff.cbBuffer, 1 | (16 << 16));
						kprintf(L"\n");
						if(OutBuff.pvBuffer)
							FreeContextBuffer(OutBuff.pvBuffer);
						DeleteSecurityContext(&hCtx);
					}
					else PRINT_ERROR(L"InitializeSecurityContext: 0x%08x\n", status);
					FreeCredentialHandle(&hCred);
				}
				else PRINT_ERROR(L"AcquireCredentialsHandle: 0x%08x\n", status);
			}
			kprintf(L"\n");
		}
		FreeContextBuffer(pPackageInfo);
	}
	else PRINT_ERROR(L"EnumerateSecurityPackages: 0x%08x\n", status);
	return STATUS_SUCCESS;
}