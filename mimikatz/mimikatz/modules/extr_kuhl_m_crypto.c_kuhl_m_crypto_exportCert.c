#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_8__ {int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {int /*<<< orphan*/  cbCertEncoded; int /*<<< orphan*/  pbCertEncoded; } ;
typedef  TYPE_1__* PCCERT_CONTEXT ;
typedef  int /*<<< orphan*/  HCERTSTORE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_2__ CRYPT_DATA_BLOB ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_CLOSE_STORE_FORCE_FLAG ; 
 int /*<<< orphan*/  CERT_STORE_ADD_NEW ; 
 int /*<<< orphan*/  CERT_STORE_CREATE_NEW_FLAG ; 
 int /*<<< orphan*/  CERT_STORE_PROV_MEMORY ; 
 scalar_t__ CertAddCertificateContextToStore (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  CertCloseStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CertFreeCertificateContext (TYPE_1__*) ; 
 int /*<<< orphan*/  CertOpenStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/ * kuhl_m_crypto_generateFileName (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const,int /*<<< orphan*/  const*,char*) ; 
 scalar_t__ kull_m_crypto_exportPfx (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_file_writeData (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kuhl_m_crypto_exportCert(PCCERT_CONTEXT pCertificate, BOOL havePrivateKey, const wchar_t * systemStore, const wchar_t * store, const DWORD index, const wchar_t * name)
{
	wchar_t *fileNameBuffer;
	BOOL isExported;
	HCERTSTORE hTempStore = CertOpenStore(CERT_STORE_PROV_MEMORY, 0, 0, CERT_STORE_CREATE_NEW_FLAG, NULL); 
	PCCERT_CONTEXT  pCertContextCopy = NULL;
	CRYPT_DATA_BLOB bDataBlob = {0, NULL};

	if(fileNameBuffer = kuhl_m_crypto_generateFileName(systemStore, store, index, name, L"der"))
	{
		isExported = kull_m_file_writeData(fileNameBuffer, pCertificate->pbCertEncoded, pCertificate->cbCertEncoded);
		kprintf(L"\tPublic export  : %s - ", isExported ? L"OK" : L"KO");
		if(isExported)
			kprintf(L"\'%s\'\n", fileNameBuffer);
		else PRINT_ERROR_AUTO(L"CreateFile");
		LocalFree(fileNameBuffer);
	}
	else PRINT_ERROR_AUTO(L"kuhl_m_crypto_generateFileName");
	
	if(havePrivateKey)
	{
		if(fileNameBuffer = kuhl_m_crypto_generateFileName(systemStore, store, index, name, L"pfx"))
		{
			isExported = FALSE;
			if(CertAddCertificateContextToStore(hTempStore, pCertificate, CERT_STORE_ADD_NEW, &pCertContextCopy))
			{
				isExported = kull_m_crypto_exportPfx(hTempStore, fileNameBuffer);
				CertFreeCertificateContext(pCertContextCopy);
			}
			kprintf(L"\tPrivate export : %s - ", isExported ? L"OK" : L"KO");
			if(isExported)
				kprintf(L"\'%s\'\n", fileNameBuffer);
			else PRINT_ERROR_AUTO(L"Export / CreateFile");
			LocalFree(fileNameBuffer);
		}
		else PRINT_ERROR_AUTO(L"kuhl_m_crypto_generateFileName");
	}
	kprintf(L"\n");
	CertCloseStore(hTempStore, CERT_CLOSE_STORE_FORCE_FLAG);
}