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
typedef  char const* LPSTR ;
typedef  char const* LPCSTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 char* CERT_HEADER ; 
 char* CERT_REQUEST_HEADER ; 
 char* CERT_REQUEST_TRAILER ; 
 char* CERT_TRAILER ; 
#define  CRYPT_STRING_BASE64 131 
#define  CRYPT_STRING_BASE64HEADER 130 
#define  CRYPT_STRING_BASE64REQUESTHEADER 129 
#define  CRYPT_STRING_BASE64X509CRLHEADER 128 
 int CRYPT_STRING_NOCR ; 
 int CRYPT_STRING_NOCRLF ; 
 int /*<<< orphan*/  ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 char* X509_HEADER ; 
 char* X509_TRAILER ; 
 int /*<<< orphan*/  encodeBase64A (int /*<<< orphan*/  const*,int,char const*,char const*,int*) ; 
 int /*<<< orphan*/  strcpy (char const*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static BOOL BinaryToBase64A(const BYTE *pbBinary,
 DWORD cbBinary, DWORD dwFlags, LPSTR pszString, DWORD *pcchString)
{
    static const char crlf[] = "\r\n", lf[] = "\n";
    BOOL ret = TRUE;
    LPCSTR header = NULL, trailer = NULL, sep;
    DWORD charsNeeded;

    if (dwFlags & CRYPT_STRING_NOCR)
        sep = lf;
    else if (dwFlags & CRYPT_STRING_NOCRLF)
        sep = "";
    else
        sep = crlf;
    switch (dwFlags & 0x0fffffff)
    {
    case CRYPT_STRING_BASE64:
        /* no header or footer */
        break;
    case CRYPT_STRING_BASE64HEADER:
        header = CERT_HEADER;
        trailer = CERT_TRAILER;
        break;
    case CRYPT_STRING_BASE64REQUESTHEADER:
        header = CERT_REQUEST_HEADER;
        trailer = CERT_REQUEST_TRAILER;
        break;
    case CRYPT_STRING_BASE64X509CRLHEADER:
        header = X509_HEADER;
        trailer = X509_TRAILER;
        break;
    }

    charsNeeded = 0;
    encodeBase64A(pbBinary, cbBinary, sep, NULL, &charsNeeded);
    if (header)
        charsNeeded += strlen(header) + strlen(sep);
    if (trailer)
        charsNeeded += strlen(trailer) + strlen(sep);

    if (pszString)
    {
        if (charsNeeded <= *pcchString)
        {
            LPSTR ptr = pszString;
            DWORD size = charsNeeded;

            if (header)
            {
                strcpy(ptr, header);
                ptr += strlen(ptr);
                strcpy(ptr, sep);
                ptr += strlen(sep);
            }
            encodeBase64A(pbBinary, cbBinary, sep, ptr, &size);
            ptr += size - 1;
            if (trailer)
            {
                strcpy(ptr, trailer);
                ptr += strlen(ptr);
               strcpy(ptr, sep);
            }
            *pcchString = charsNeeded - 1;
        }
        else
        {
            *pcchString = charsNeeded;
            SetLastError(ERROR_INSUFFICIENT_BUFFER);
            ret = FALSE;
        }
    }
    else
        *pcchString = charsNeeded;

    return ret;
}