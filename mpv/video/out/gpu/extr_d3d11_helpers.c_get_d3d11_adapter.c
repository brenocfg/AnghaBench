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
struct mp_log {int dummy; } ;
struct bstr {scalar_t__ len; } ;
struct TYPE_3__ {int /*<<< orphan*/  VendorId; int /*<<< orphan*/  Description; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  IDXGIFactory1 ;
typedef  int /*<<< orphan*/  IDXGIAdapter1 ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_1__ DXGI_ADAPTER_DESC1 ;

/* Variables and functions */
 scalar_t__ DXGI_ERROR_NOT_FOUND ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ IDXGIAdapter1_GetDesc1 (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ IDXGIFactory1_EnumAdapters1 (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IID_IDXGIFactory1 ; 
 int /*<<< orphan*/  SAFE_RELEASE (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  bstr0 (char*) ; 
 scalar_t__ bstr_case_startswith (int /*<<< orphan*/ ,struct bstr) ; 
 int /*<<< orphan*/  bstr_xappend_asprintf (int /*<<< orphan*/ *,struct bstr*,char*,unsigned int,int /*<<< orphan*/ ,char*) ; 
 unsigned int mp_HRESULT_to_str (scalar_t__) ; 
 int /*<<< orphan*/  mp_fatal (struct mp_log*,char*,unsigned int) ; 
 char* mp_to_utf8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pCreateDXGIFactory1 (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 

__attribute__((used)) static IDXGIAdapter1 *get_d3d11_adapter(struct mp_log *log,
                                        struct bstr requested_adapter_name,
                                        struct bstr *listing)
{
    HRESULT hr = S_OK;
    IDXGIFactory1 *factory;
    IDXGIAdapter1 *picked_adapter = NULL;

    hr = pCreateDXGIFactory1(&IID_IDXGIFactory1, (void **)&factory);
    if (FAILED(hr)) {
        mp_fatal(log, "Failed to create a DXGI factory: %s\n",
                 mp_HRESULT_to_str(hr));
        return NULL;
    }

    for (unsigned int adapter_num = 0; hr != DXGI_ERROR_NOT_FOUND; adapter_num++)
    {
        IDXGIAdapter1 *adapter = NULL;
        DXGI_ADAPTER_DESC1 desc = { 0 };
        char *adapter_description = NULL;

        hr = IDXGIFactory1_EnumAdapters1(factory, adapter_num, &adapter);
        if (FAILED(hr)) {
            if (hr != DXGI_ERROR_NOT_FOUND) {
                mp_fatal(log, "Failed to enumerate at adapter %u\n",
                         adapter_num);
            }
            continue;
        }

        if (FAILED(IDXGIAdapter1_GetDesc1(adapter, &desc))) {
            mp_fatal(log, "Failed to get adapter description when listing at adapter %u\n",
                     adapter_num);
            continue;
        }

        adapter_description = mp_to_utf8(NULL, desc.Description);

        if (listing) {
            bstr_xappend_asprintf(NULL, listing,
                                  "Adapter %u: vendor: %u, description: %s\n",
                                  adapter_num, desc.VendorId,
                                  adapter_description);
        }

        if (requested_adapter_name.len &&
            bstr_case_startswith(bstr0(adapter_description),
                                 requested_adapter_name))
        {
            picked_adapter = adapter;
        }

        talloc_free(adapter_description);

        if (picked_adapter) {
            break;
        }

        SAFE_RELEASE(adapter);
    }

    SAFE_RELEASE(factory);

    return picked_adapter;
}