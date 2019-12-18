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
struct host_object_params {int /*<<< orphan*/  stream; int /*<<< orphan*/  iid; int /*<<< orphan*/  clsid; int /*<<< orphan*/  apartment_threaded; int /*<<< orphan*/  regdata; } ;
struct apartment {int dummy; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoMarshalInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IStream_Seek (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  MSHCTX_INPROC ; 
 int /*<<< orphan*/  MSHLFLAGS_NORMAL ; 
 int /*<<< orphan*/  REGDB_E_CLASSNOTREG ; 
 int /*<<< orphan*/  STREAM_SEEK_SET ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apartment_getclassobject (struct apartment*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_object_dll_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT apartment_hostobject(struct apartment *apt,
                                    const struct host_object_params *params)
{
    IUnknown *object;
    HRESULT hr;
    static const LARGE_INTEGER llZero;
    WCHAR dllpath[MAX_PATH+1];

    TRACE("clsid %s, iid %s\n", debugstr_guid(&params->clsid), debugstr_guid(&params->iid));

    if (!get_object_dll_path(&params->regdata, dllpath, ARRAY_SIZE(dllpath)))
    {
        /* failure: CLSID is not found in registry */
        WARN("class %s not registered inproc\n", debugstr_guid(&params->clsid));
        return REGDB_E_CLASSNOTREG;
    }

    hr = apartment_getclassobject(apt, dllpath, params->apartment_threaded,
                                  &params->clsid, &params->iid, (void **)&object);
    if (FAILED(hr))
        return hr;

    hr = CoMarshalInterface(params->stream, &params->iid, object, MSHCTX_INPROC, NULL, MSHLFLAGS_NORMAL);
    if (FAILED(hr))
        IUnknown_Release(object);
    IStream_Seek(params->stream, llZero, STREAM_SEEK_SET, NULL);

    return hr;
}