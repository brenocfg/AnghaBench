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
typedef  int /*<<< orphan*/  DWORD ;
typedef  int D3DXPARAMETER_TYPE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  D3DXPT_BOOL 130 
#define  D3DXPT_FLOAT 129 
#define  D3DXPT_INT 128 
 int /*<<< orphan*/  get_bool (int,void const*) ; 
 float get_float (int,void const*) ; 
 int get_int (int,void const*) ; 

__attribute__((used)) static inline void set_number(void *outdata, D3DXPARAMETER_TYPE outtype, const void *indata, D3DXPARAMETER_TYPE intype)
{
    if (outtype == intype)
    {
        *(DWORD *)outdata = *(DWORD *)indata;
        return;
    }

    switch (outtype)
    {
        case D3DXPT_FLOAT:
            *(float *)outdata = get_float(intype, indata);
            break;

        case D3DXPT_BOOL:
            *(BOOL *)outdata = get_bool(intype, indata);
            break;

        case D3DXPT_INT:
            *(int *)outdata = get_int(intype, indata);
            break;

        default:
            *(DWORD *)outdata = 0;
            break;
    }
}