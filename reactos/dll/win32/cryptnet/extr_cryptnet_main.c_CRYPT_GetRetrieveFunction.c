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
typedef  int /*<<< orphan*/  components ;
struct TYPE_3__ {int member_0; int dwSchemeLength; int nScheme; int /*<<< orphan*/  lpszScheme; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_1__ URL_COMPONENTSW ;
typedef  int /*<<< orphan*/ * SchemeDllRetrieveEncodedObjectW ;
typedef  int /*<<< orphan*/ * LPSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/ * HCRYPTOIDFUNCSET ;
typedef  scalar_t__ HCRYPTOIDFUNCADDR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ CryptGetOIDFunctionAddress (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**,scalar_t__*) ; 
 int /*<<< orphan*/ * CryptInitOIDFunctionSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CryptMemAlloc (int) ; 
 int /*<<< orphan*/  CryptMemFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/ * FTP_RetrieveEncodedObjectW ; 
 int /*<<< orphan*/ * File_RetrieveEncodedObjectW ; 
 int /*<<< orphan*/ * HTTP_RetrieveEncodedObjectW ; 
#define  INTERNET_SCHEME_FILE 130 
#define  INTERNET_SCHEME_FTP 129 
#define  INTERNET_SCHEME_HTTP 128 
 scalar_t__ InternetCrackUrlW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SCHEME_OID_RETRIEVE_ENCODED_OBJECTW_FUNC ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,...) ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL CRYPT_GetRetrieveFunction(LPCWSTR pszURL,
 SchemeDllRetrieveEncodedObjectW *pFunc, HCRYPTOIDFUNCADDR *phFunc)
{
    URL_COMPONENTSW components = { sizeof(components), 0 };
    BOOL ret;

    TRACE("(%s, %p, %p)\n", debugstr_w(pszURL), pFunc, phFunc);

    *pFunc = NULL;
    *phFunc = 0;
    components.dwSchemeLength = 1;
    ret = InternetCrackUrlW(pszURL, 0, 0, &components);
    if (ret)
    {
        /* Microsoft always uses CryptInitOIDFunctionSet/
         * CryptGetOIDFunctionAddress, but there doesn't seem to be a pressing
         * reason to do so for builtin schemes.
         */
        switch (components.nScheme)
        {
        case INTERNET_SCHEME_FTP:
            *pFunc = FTP_RetrieveEncodedObjectW;
            break;
        case INTERNET_SCHEME_HTTP:
            *pFunc = HTTP_RetrieveEncodedObjectW;
            break;
        case INTERNET_SCHEME_FILE:
            *pFunc = File_RetrieveEncodedObjectW;
            break;
        default:
        {
            int len = WideCharToMultiByte(CP_ACP, 0, components.lpszScheme,
             components.dwSchemeLength, NULL, 0, NULL, NULL);

            if (len)
            {
                LPSTR scheme = CryptMemAlloc(len);

                if (scheme)
                {
                    static HCRYPTOIDFUNCSET set = NULL;

                    if (!set)
                        set = CryptInitOIDFunctionSet(
                         SCHEME_OID_RETRIEVE_ENCODED_OBJECTW_FUNC, 0);
                    WideCharToMultiByte(CP_ACP, 0, components.lpszScheme,
                     components.dwSchemeLength, scheme, len, NULL, NULL);
                    ret = CryptGetOIDFunctionAddress(set, X509_ASN_ENCODING,
                     scheme, 0, (void **)pFunc, phFunc);
                    CryptMemFree(scheme);
                }
                else
                {
                    SetLastError(ERROR_OUTOFMEMORY);
                    ret = FALSE;
                }
            }
            else
                ret = FALSE;
        }
        }
    }
    TRACE("returning %d\n", ret);
    return ret;
}