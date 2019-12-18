#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {int MaxCount; } ;
typedef  int /*<<< orphan*/  SHORT ;
typedef  int* PFORMAT_STRING ;
typedef  TYPE_1__ MIDL_STUB_MESSAGE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int ComplexStructSize (TYPE_1__*,int*) ; 
 int* ComputeConformance (TYPE_1__*,int /*<<< orphan*/ *,int*,int const) ; 
 int* ComputeVariance (TYPE_1__*,int /*<<< orphan*/ *,int*,int) ; 
#define  FC_BOGUS_ARRAY 147 
#define  FC_BOGUS_STRUCT 146 
#define  FC_CARRAY 145 
#define  FC_CSTRING 144 
#define  FC_CVARRAY 143 
#define  FC_C_CSTRING 142 
#define  FC_C_WSTRING 141 
#define  FC_FP 140 
#define  FC_IP 139 
#define  FC_LGFARRAY 138 
#define  FC_LGVARRAY 137 
#define  FC_OP 136 
#define  FC_PSTRUCT 135 
#define  FC_RP 134 
 int FC_SIMPLE_POINTER ; 
#define  FC_SMFARRAY 133 
#define  FC_SMVARRAY 132 
 int FC_STRING_SIZED ; 
#define  FC_STRUCT 131 
#define  FC_UP 130 
#define  FC_USER_MARSHAL 129 
#define  FC_WSTRING 128 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 

__attribute__((used)) static DWORD calc_arg_size(MIDL_STUB_MESSAGE *pStubMsg, PFORMAT_STRING pFormat)
{
    DWORD size;
    switch(*pFormat)
    {
    case FC_RP:
        if (pFormat[1] & FC_SIMPLE_POINTER)
        {
            size = 0;
            break;
        }
        size = calc_arg_size(pStubMsg, &pFormat[2] + *(const SHORT*)&pFormat[2]);
        break;
    case FC_STRUCT:
    case FC_PSTRUCT:
        size = *(const WORD*)(pFormat + 2);
        break;
    case FC_BOGUS_STRUCT:
        size = *(const WORD*)(pFormat + 2);
        if(*(const WORD*)(pFormat + 4))
            FIXME("Unhandled conformant description\n");
        break;
    case FC_CARRAY:
    case FC_CVARRAY:
        size = *(const WORD*)(pFormat + 2);
        ComputeConformance(pStubMsg, NULL, pFormat + 4, 0);
        size *= pStubMsg->MaxCount;
        break;
    case FC_SMFARRAY:
    case FC_SMVARRAY:
        size = *(const WORD*)(pFormat + 2);
        break;
    case FC_LGFARRAY:
    case FC_LGVARRAY:
        size = *(const DWORD*)(pFormat + 2);
        break;
    case FC_BOGUS_ARRAY:
        pFormat = ComputeConformance(pStubMsg, NULL, pFormat + 4, *(const WORD*)&pFormat[2]);
        TRACE("conformance = %ld\n", pStubMsg->MaxCount);
        pFormat = ComputeVariance(pStubMsg, NULL, pFormat, pStubMsg->MaxCount);
        size = ComplexStructSize(pStubMsg, pFormat);
        size *= pStubMsg->MaxCount;
        break;
    case FC_USER_MARSHAL:
        size = *(const WORD*)(pFormat + 4);
        break;
    case FC_CSTRING:
        size = *(const WORD*)(pFormat + 2);
        break;
    case FC_WSTRING:
        size = *(const WORD*)(pFormat + 2) * sizeof(WCHAR);
        break;
    case FC_C_CSTRING:
    case FC_C_WSTRING:
        if (*pFormat == FC_C_CSTRING)
            size = sizeof(CHAR);
        else
            size = sizeof(WCHAR);
        if (pFormat[1] == FC_STRING_SIZED)
            ComputeConformance(pStubMsg, NULL, pFormat + 2, 0);
        else
            pStubMsg->MaxCount = 0;
        size *= pStubMsg->MaxCount;
        break;
    default:
        FIXME("Unhandled type %02x\n", *pFormat);
        /* fallthrough */
    case FC_UP:
    case FC_OP:
    case FC_FP:
    case FC_IP:
        size = sizeof(void *);
        break;
    }
    return size;
}