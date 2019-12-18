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
typedef  int HRESULT ;

/* Variables and functions */
 int D3DXFERR_BADFILEFLOATSIZE ; 
 int D3DXFERR_BADFILETYPE ; 
 int D3DXFERR_BADFILEVERSION ; 
 int D3DXFERR_BADVALUE ; 
 int D3DXFERR_PARSEERROR ; 
#define  DXFILEERR_BADFILEFLOATSIZE 132 
#define  DXFILEERR_BADFILETYPE 131 
#define  DXFILEERR_BADFILEVERSION 130 
#define  DXFILEERR_BADVALUE 129 
#define  DXFILEERR_PARSEERROR 128 
 int E_FAIL ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 

__attribute__((used)) static HRESULT error_dxfile_to_d3dxfile(HRESULT error)
{
    switch (error)
    {
        case DXFILEERR_BADFILETYPE:
            return D3DXFERR_BADFILETYPE;
        case DXFILEERR_BADFILEVERSION:
            return D3DXFERR_BADFILEVERSION;
        case DXFILEERR_BADFILEFLOATSIZE:
            return D3DXFERR_BADFILEFLOATSIZE;
        case DXFILEERR_PARSEERROR:
            return D3DXFERR_PARSEERROR;
        case DXFILEERR_BADVALUE:
            return D3DXFERR_BADVALUE;
        default:
            FIXME("Cannot map error %#x\n", error);
            return E_FAIL;
    }
}