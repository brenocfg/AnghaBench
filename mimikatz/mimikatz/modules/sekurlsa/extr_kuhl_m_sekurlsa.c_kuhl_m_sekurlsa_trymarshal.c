#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_9__ {int /*<<< orphan*/  cbBlob; int /*<<< orphan*/  pbBlob; } ;
struct TYPE_8__ {int cbSize; int /*<<< orphan*/  rgbHashOfCert; } ;
struct TYPE_7__ {scalar_t__ Length; scalar_t__ Buffer; } ;
struct TYPE_6__ {int /*<<< orphan*/  UserName; } ;
typedef  scalar_t__ PWSTR ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PUSERNAME_TARGET_CREDENTIAL_INFO ;
typedef  TYPE_2__* PCUNICODE_STRING ;
typedef  TYPE_3__* PCERT_CREDENTIAL_INFO ;
typedef  TYPE_4__* PBINARY_BLOB_CREDENTIAL_INFO ;
typedef  int /*<<< orphan*/  CRED_MARSHAL_TYPE ;
typedef  int /*<<< orphan*/  CERT_CREDENTIAL_INFO ;

/* Variables and functions */
#define  BinaryBlobCredential 131 
 int /*<<< orphan*/  CERT_HASH_LENGTH ; 
#define  CertCredential 130 
 scalar_t__ CredIsMarshaledCredential (scalar_t__) ; 
 scalar_t__ CredUnmarshalCredential (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  LocalFree (scalar_t__) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,int) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  RtlCopyMemory (scalar_t__,scalar_t__,scalar_t__) ; 
#define  UsernameForPackedCredentials 129 
#define  UsernameTargetCredential 128 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

VOID kuhl_m_sekurlsa_trymarshal(PCUNICODE_STRING MarshaledCredential)
{
	PWSTR buffer;
	CRED_MARSHAL_TYPE type;
	PVOID Credential;

	if(MarshaledCredential->Length && MarshaledCredential->Buffer)
	{
		if(buffer = (PWSTR) LocalAlloc(LPTR, MarshaledCredential->Length + sizeof(wchar_t)))
		{
			RtlCopyMemory(buffer, MarshaledCredential->Buffer, MarshaledCredential->Length);
			if(CredIsMarshaledCredential(buffer))
			{
				kprintf(L"\n\t * Marshaled: ");
				if(CredUnmarshalCredential(buffer, &type, &Credential))
				{
					switch(type)
					{
					case CertCredential:
						if(((PCERT_CREDENTIAL_INFO) Credential)->cbSize == sizeof(CERT_CREDENTIAL_INFO))
						{
							kprintf(L"[Cert] SHA1:");
							kull_m_string_wprintf_hex(((PCERT_CREDENTIAL_INFO) Credential)->rgbHashOfCert, CERT_HASH_LENGTH, 0);
						}
						else PRINT_ERROR(L"Credential->cbSize is %u\n", ((PCERT_CREDENTIAL_INFO) Credential)->cbSize);
						break;
					case UsernameTargetCredential:
						kprintf(L"[UsernameTarget] %s\n", ((PUSERNAME_TARGET_CREDENTIAL_INFO) Credential)->UserName);
						break;
					case BinaryBlobCredential:
						kprintf(L"[BinaryBlob] ");
						kull_m_string_wprintf_hex(((PBINARY_BLOB_CREDENTIAL_INFO) Credential)->pbBlob, ((PBINARY_BLOB_CREDENTIAL_INFO) Credential)->cbBlob, 1);
						break;
					case UsernameForPackedCredentials:
						kprintf(L"[UsernameForPacked] ?");
						break;
					default:
						kprintf(L"[?] ?");
					}
				}
				else PRINT_ERROR_AUTO(L"CredUnmarshalCredential");
			}
			LocalFree(buffer);
		}
	}
}