#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mp_log {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  pwszVal; } ;
typedef  TYPE_1__ PROPVARIANT ;
typedef  int /*<<< orphan*/  IPropertyStore ;
typedef  int /*<<< orphan*/  IMMDevice ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_ON_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMMDevice_OpenPropertyStore (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IPropertyStore_GetValue (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  PropVariantClear (TYPE_1__*) ; 
 int /*<<< orphan*/  PropVariantInit (TYPE_1__*) ; 
 int /*<<< orphan*/  SAFE_RELEASE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STGM_READ ; 
 int /*<<< orphan*/  mp_HRESULT_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_PKEY_Device_FriendlyName ; 
 char* mp_to_utf8 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_warn (struct mp_log*,char*,int /*<<< orphan*/ ) ; 
 char* talloc_strdup (void*,char*) ; 

__attribute__((used)) static char* get_device_name(struct mp_log *l, void *talloc_ctx, IMMDevice *pDevice)
{
    char *namestr = NULL;
    IPropertyStore *pProps = NULL;
    PROPVARIANT devname;
    PropVariantInit(&devname);

    HRESULT hr = IMMDevice_OpenPropertyStore(pDevice, STGM_READ, &pProps);
    EXIT_ON_ERROR(hr);

    hr = IPropertyStore_GetValue(pProps, &mp_PKEY_Device_FriendlyName,
                                 &devname);
    EXIT_ON_ERROR(hr);

    namestr = mp_to_utf8(talloc_ctx, devname.pwszVal);

exit_label:
    if (FAILED(hr))
        mp_warn(l, "Failed getting device name: %s\n", mp_HRESULT_to_str(hr));
    PropVariantClear(&devname);
    SAFE_RELEASE(pProps);
    return namestr ? namestr : talloc_strdup(talloc_ctx, "");
}