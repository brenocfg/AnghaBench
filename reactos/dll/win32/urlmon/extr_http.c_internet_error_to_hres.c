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
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
#define  ERROR_HTTP_REDIRECT_NEEDS_CONFIRMATION 139 
#define  ERROR_INTERNET_CLIENT_AUTH_CERT_NEEDED 138 
#define  ERROR_INTERNET_HTTPS_TO_HTTP_ON_REDIR 137 
#define  ERROR_INTERNET_HTTP_TO_HTTPS_ON_REDIR 136 
#define  ERROR_INTERNET_INVALID_CA 135 
#define  ERROR_INTERNET_SEC_CERT_CN_INVALID 134 
#define  ERROR_INTERNET_SEC_CERT_DATE_INVALID 133 
#define  ERROR_INTERNET_SEC_CERT_ERRORS 132 
#define  ERROR_INTERNET_SEC_CERT_NO_REV 131 
#define  ERROR_INTERNET_SEC_CERT_REVOKED 130 
#define  ERROR_INTERNET_SEC_CERT_REV_FAILED 129 
#define  ERROR_INTERNET_SEC_INVALID_CERT 128 
 int /*<<< orphan*/  INET_E_DOWNLOAD_FAILURE ; 
 int /*<<< orphan*/  INET_E_INVALID_CERTIFICATE ; 
 int /*<<< orphan*/  INET_E_REDIRECT_FAILED ; 

__attribute__((used)) static inline HRESULT internet_error_to_hres(DWORD error)
{
    switch(error)
    {
    case ERROR_INTERNET_SEC_CERT_DATE_INVALID:
    case ERROR_INTERNET_SEC_CERT_CN_INVALID:
    case ERROR_INTERNET_INVALID_CA:
    case ERROR_INTERNET_CLIENT_AUTH_CERT_NEEDED:
    case ERROR_INTERNET_SEC_INVALID_CERT:
    case ERROR_INTERNET_SEC_CERT_ERRORS:
    case ERROR_INTERNET_SEC_CERT_REV_FAILED:
    case ERROR_INTERNET_SEC_CERT_NO_REV:
    case ERROR_INTERNET_SEC_CERT_REVOKED:
        return INET_E_INVALID_CERTIFICATE;
    case ERROR_INTERNET_HTTP_TO_HTTPS_ON_REDIR:
    case ERROR_INTERNET_HTTPS_TO_HTTP_ON_REDIR:
    case ERROR_HTTP_REDIRECT_NEEDS_CONFIRMATION:
        return INET_E_REDIRECT_FAILED;
    default:
        return INET_E_DOWNLOAD_FAILURE;
    }
}