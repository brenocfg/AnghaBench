#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int len; int* data; } ;
struct TYPE_5__ {TYPE_1__ custdata_seg; } ;
typedef  TYPE_2__ WMSFT_TLBFile ;
typedef  int VARTYPE ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int SysStringLen (int*) ; 
#define  VT_BOOL 140 
#define  VT_BSTR 139 
#define  VT_HRESULT 138 
#define  VT_I1 137 
#define  VT_I2 136 
#define  VT_I4 135 
#define  VT_INT 134 
#define  VT_PTR 133 
#define  VT_R4 132 
#define  VT_UI1 131 
#define  VT_UI2 130 
#define  VT_UI4 129 
#define  VT_UINT 128 
 int* V_BSTR (int /*<<< orphan*/ *) ; 
 int V_UI4 (int /*<<< orphan*/ *) ; 
 int V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantChangeType (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* heap_alloc (int) ; 
 void* heap_realloc (int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD WMSFT_encode_variant(VARIANT *value, WMSFT_TLBFile *file)
{
    VARIANT v = *value;
    VARTYPE arg_type = V_VT(value);
    int mask = 0;
    HRESULT hres;
    DWORD ret = file->custdata_seg.len;

    if(arg_type == VT_INT)
        arg_type = VT_I4;
    if(arg_type == VT_UINT)
        arg_type = VT_UI4;

    v = *value;
    if(V_VT(value) != arg_type) {
        hres = VariantChangeType(&v, value, 0, arg_type);
        if(FAILED(hres)){
            ERR("VariantChangeType failed: %08x\n", hres);
            return -1;
        }
    }

    /* Check if default value can be stored in-place */
    switch(arg_type){
    case VT_I4:
    case VT_UI4:
        mask = 0x3ffffff;
        if(V_UI4(&v) > 0x3ffffff)
            break;
        /* fall through */
    case VT_I1:
    case VT_UI1:
    case VT_BOOL:
        if(!mask)
            mask = 0xff;
        /* fall through */
    case VT_I2:
    case VT_UI2:
        if(!mask)
            mask = 0xffff;
        return ((0x80 + 0x4 * V_VT(value)) << 24) | (V_UI4(&v) & mask);
    }

    /* have to allocate space in custdata_seg */
    switch(arg_type) {
    case VT_I4:
    case VT_R4:
    case VT_UI4:
    case VT_INT:
    case VT_UINT:
    case VT_HRESULT:
    case VT_PTR: {
        /* Construct the data to be allocated */
        int *data;

        if(file->custdata_seg.data){
            file->custdata_seg.data = heap_realloc(file->custdata_seg.data, file->custdata_seg.len + sizeof(int) * 2);
            data = (int *)(((char *)file->custdata_seg.data) + file->custdata_seg.len);
            file->custdata_seg.len += sizeof(int) * 2;
        }else{
            file->custdata_seg.len = sizeof(int) * 2;
            data = file->custdata_seg.data = heap_alloc(file->custdata_seg.len);
        }

        data[0] = V_VT(value) + (V_UI4(&v) << 16);
        data[1] = (V_UI4(&v) >> 16) + 0x57570000;

        /* TODO: Check if the encoded data is already present in custdata_seg */

        return ret;
    }

    case VT_BSTR: {
        int i, len = (6+SysStringLen(V_BSTR(&v))+3) & ~0x3;
        char *data;

        if(file->custdata_seg.data){
            file->custdata_seg.data = heap_realloc(file->custdata_seg.data, file->custdata_seg.len + len);
            data = ((char *)file->custdata_seg.data) + file->custdata_seg.len;
            file->custdata_seg.len += len;
        }else{
            file->custdata_seg.len = len;
            data = file->custdata_seg.data = heap_alloc(file->custdata_seg.len);
        }

        *((unsigned short *)data) = V_VT(value);
        *((unsigned int *)(data+2)) = SysStringLen(V_BSTR(&v));
        for(i=0; i<SysStringLen(V_BSTR(&v)); i++) {
            if(V_BSTR(&v)[i] <= 0x7f)
                data[i+6] = V_BSTR(&v)[i];
            else
                data[i+6] = '?';
        }
        WideCharToMultiByte(CP_ACP, 0, V_BSTR(&v), SysStringLen(V_BSTR(&v)), &data[6], len-6, NULL, NULL);
        for(i=6+SysStringLen(V_BSTR(&v)); i<len; i++)
            data[i] = 0x57;

        /* TODO: Check if the encoded data is already present in custdata_seg */

        return ret;
    }
    default:
        FIXME("Argument type not yet handled\n");
        return -1;
    }
}