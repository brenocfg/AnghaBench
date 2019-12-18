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
typedef  int /*<<< orphan*/  IWSCProductList ;
typedef  int /*<<< orphan*/  IID ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HMODULE ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ ) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LoadLibraryW (char*) ; 
 int /*<<< orphan*/  WSC_SECURITY_PROVIDER_ANTISPYWARE ; 
 int /*<<< orphan*/  WSC_SECURITY_PROVIDER_ANTIVIRUS ; 
 int /*<<< orphan*/  WSC_SECURITY_PROVIDER_FIREWALL ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  log_security_products_by_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void log_security_products(void)
{
	IWSCProductList *prod_list = NULL;
	HMODULE h_wsc;
	HRESULT hr;

	/* We load the DLL rather than import wcsapi.lib because the clsid /
	 * iid only exists on Windows 8 or higher. */

	h_wsc = LoadLibraryW(L"wscapi.dll");
	if (!h_wsc)
		return;

	const CLSID *prod_list_clsid =
		(const CLSID *)GetProcAddress(h_wsc, "CLSID_WSCProductList");
	const IID *prod_list_iid =
		(const IID *)GetProcAddress(h_wsc, "IID_IWSCProductList");

	if (prod_list_clsid && prod_list_iid) {
		blog(LOG_INFO, "Sec. Software Status:");

		hr = CoCreateInstance(prod_list_clsid, NULL,
				      CLSCTX_INPROC_SERVER, prod_list_iid,
				      &prod_list);
		if (!FAILED(hr)) {
			log_security_products_by_type(
				prod_list, WSC_SECURITY_PROVIDER_ANTIVIRUS);
		}

		hr = CoCreateInstance(prod_list_clsid, NULL,
				      CLSCTX_INPROC_SERVER, prod_list_iid,
				      &prod_list);
		if (!FAILED(hr)) {
			log_security_products_by_type(
				prod_list, WSC_SECURITY_PROVIDER_FIREWALL);
		}

		hr = CoCreateInstance(prod_list_clsid, NULL,
				      CLSCTX_INPROC_SERVER, prod_list_iid,
				      &prod_list);
		if (!FAILED(hr)) {
			log_security_products_by_type(
				prod_list, WSC_SECURITY_PROVIDER_ANTISPYWARE);
		}
	}

	FreeLibrary(h_wsc);
}