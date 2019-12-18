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
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  IUri ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 int CreateUri (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int E_INVALIDARG ; 
 scalar_t__ FAILED (int) ; 
 int /*<<< orphan*/  IUri_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  URLZONE_INVALID ; 
 int /*<<< orphan*/  Uri_CREATE_ALLOW_IMPLICIT_FILE_SCHEME ; 
 int generate_security_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int map_url_to_zone (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT get_security_id_for_url(LPCWSTR url, BYTE *secid, DWORD *secid_len)
{
    HRESULT hres;
    DWORD zone = URLZONE_INVALID;
    LPWSTR secur_url = NULL;
    IUri *uri;

    hres = map_url_to_zone(url, &zone, &secur_url);
    if(FAILED(hres))
        return hres == 0x80041001 ? E_INVALIDARG : hres;

    hres = CreateUri(secur_url, Uri_CREATE_ALLOW_IMPLICIT_FILE_SCHEME, 0, &uri);
    CoTaskMemFree(secur_url);
    if(FAILED(hres))
        return hres;

    hres = generate_security_id(uri, secid, secid_len, zone);
    IUri_Release(uri);

    return hres;
}