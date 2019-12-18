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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/ * PCCERT_CONTEXT ;
typedef  scalar_t__* LPWSTR ;
typedef  scalar_t__* LPCWSTR ;
typedef  int /*<<< orphan*/  HCERTSTORE ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__* CryptMemAlloc (int) ; 
 int /*<<< orphan*/  CryptMemFree (scalar_t__*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cert_compare_certs_in_store (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,scalar_t__*) ; 
 int /*<<< orphan*/  compare_cert_by_name_str ; 
 int /*<<< orphan*/  debugstr_w (void const*) ; 
 int /*<<< orphan*/ * find_cert_any (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int strlenW (void const*) ; 
 scalar_t__ tolowerW (scalar_t__) ; 

__attribute__((used)) static PCCERT_CONTEXT find_cert_by_name_str_w(HCERTSTORE store, DWORD dwType,
 DWORD dwFlags, const void *pvPara, PCCERT_CONTEXT prev)
{
    PCCERT_CONTEXT found = NULL;

    TRACE("%s\n", debugstr_w(pvPara));

    if (pvPara)
    {
        DWORD len = strlenW(pvPara);
        LPWSTR str = CryptMemAlloc((len + 1) * sizeof(WCHAR));

        if (str)
        {
            LPCWSTR src;
            LPWSTR dst;

            for (src = pvPara, dst = str; *src; src++, dst++)
                *dst = tolowerW(*src);
            *dst = 0;
           found = cert_compare_certs_in_store(store, prev,
            compare_cert_by_name_str, dwType, dwFlags, str);
           CryptMemFree(str);
        }
    }
    else
        found = find_cert_any(store, dwType, dwFlags, NULL, prev);
    return found;
}