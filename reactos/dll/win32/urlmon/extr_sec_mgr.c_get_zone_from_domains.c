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
typedef  int /*<<< orphan*/  IUri ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 scalar_t__ IUri_GetHost (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IUri_GetScheme (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ IUri_GetSchemeName (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SysStringLen (int /*<<< orphan*/ *) ; 
 scalar_t__ URLZONE_INVALID ; 
 scalar_t__ URL_SCHEME_FILE ; 
 scalar_t__ URL_SCHEME_UNKNOWN ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 scalar_t__ is_hierarchical_scheme (scalar_t__) ; 
 scalar_t__ search_for_domain_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  wszZoneMapDomainsKey ; 

__attribute__((used)) static HRESULT get_zone_from_domains(IUri *uri, DWORD *zone)
{
    HRESULT hres;
    BSTR host, scheme;
    DWORD res;
    HKEY domains;
    DWORD scheme_type;

    hres = IUri_GetScheme(uri, &scheme_type);
    if(FAILED(hres))
        return hres;

    /* Windows doesn't play nice with unknown scheme types when it tries
     * to check if a host name maps into any domains.
     */
    if(scheme_type == URL_SCHEME_UNKNOWN)
        return S_FALSE;

    hres = IUri_GetHost(uri, &host);
    if(FAILED(hres))
        return hres;

    /* Known hierarchical scheme types must have a host. If they don't Windows
     * assigns URLZONE_INVALID to the zone.
     */
    if((scheme_type != URL_SCHEME_UNKNOWN && scheme_type != URL_SCHEME_FILE)
        && is_hierarchical_scheme(scheme_type) && !*host) {
        *zone = URLZONE_INVALID;

        SysFreeString(host);

        /* The MapUrlToZone functions return S_OK when this condition occurs. */
        return S_OK;
    }

    hres = IUri_GetSchemeName(uri, &scheme);
    if(FAILED(hres)) {
        SysFreeString(host);
        return hres;
    }

    /* First try CURRENT_USER. */
    res = RegOpenKeyW(HKEY_CURRENT_USER, wszZoneMapDomainsKey, &domains);
    if(res == ERROR_SUCCESS) {
        hres = search_for_domain_mapping(domains, scheme, host, SysStringLen(host), zone);
        RegCloseKey(domains);
    } else
        WARN("Failed to open HKCU's %s key\n", debugstr_w(wszZoneMapDomainsKey));

    /* If that doesn't work try LOCAL_MACHINE. */
    if(hres == S_FALSE) {
        res = RegOpenKeyW(HKEY_LOCAL_MACHINE, wszZoneMapDomainsKey, &domains);
        if(res == ERROR_SUCCESS) {
            hres = search_for_domain_mapping(domains, scheme, host, SysStringLen(host), zone);
            RegCloseKey(domains);
        } else
            WARN("Failed to open HKLM's %s key\n", debugstr_w(wszZoneMapDomainsKey));
    }

    SysFreeString(host);
    SysFreeString(scheme);
    return hres;
}