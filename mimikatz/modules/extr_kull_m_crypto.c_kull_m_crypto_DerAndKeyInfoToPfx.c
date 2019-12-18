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
typedef  scalar_t__ PCRYPT_KEY_PROV_INFO ;
typedef  int /*<<< orphan*/  PCCERT_CONTEXT ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ LPCVOID ;
typedef  int /*<<< orphan*/  LPCBYTE ;
typedef  int /*<<< orphan*/  HCERTSTORE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_CLOSE_STORE_FORCE_FLAG ; 
 int /*<<< orphan*/  CERT_KEY_PROV_INFO_PROP_ID ; 
 int /*<<< orphan*/  CERT_STORE_ADD_NEW ; 
 int /*<<< orphan*/  CERT_STORE_CREATE_NEW_FLAG ; 
 int /*<<< orphan*/  CERT_STORE_PROV_MEMORY ; 
 scalar_t__ CertAddEncodedCertificateToStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CertCloseStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CertFreeCertificateContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CertOpenStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CertSetCertificateContextProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 
 int /*<<< orphan*/  kull_m_crypto_exportPfx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOL kull_m_crypto_DerAndKeyInfoToPfx(LPCVOID der, DWORD derLen, PCRYPT_KEY_PROV_INFO pInfo, LPCWSTR filename)
{
	BOOL isExported = FALSE;
	HCERTSTORE hTempStore;
	PCCERT_CONTEXT pCertContext;
	if(hTempStore = CertOpenStore(CERT_STORE_PROV_MEMORY, 0, 0, CERT_STORE_CREATE_NEW_FLAG, NULL))
	{
		if(CertAddEncodedCertificateToStore(hTempStore, X509_ASN_ENCODING, (LPCBYTE) der, derLen, CERT_STORE_ADD_NEW, &pCertContext))
		{
			if(CertSetCertificateContextProperty(pCertContext, CERT_KEY_PROV_INFO_PROP_ID, 0, (LPCVOID) pInfo))
				isExported = kull_m_crypto_exportPfx(hTempStore, filename);
			else PRINT_ERROR_AUTO(L"CertSetCertificateContextProperty(CERT_KEY_PROV_INFO_PROP_ID)");
			CertFreeCertificateContext(pCertContext);
		}
		else PRINT_ERROR_AUTO(L"CertAddEncodedCertificateToStore");
		CertCloseStore(hTempStore, CERT_CLOSE_STORE_FORCE_FLAG);
	}
	return isExported;
}