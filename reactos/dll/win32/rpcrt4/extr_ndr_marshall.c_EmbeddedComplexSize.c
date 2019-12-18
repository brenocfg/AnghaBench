#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
typedef  int /*<<< orphan*/  USHORT ;
typedef  int /*<<< orphan*/  ULONGLONG ;
typedef  int const ULONG ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_2__ {int flags_type; } ;
typedef  int SHORT ;
typedef  int* PFORMAT_STRING ;
typedef  TYPE_1__ NDR_RANGE ;
typedef  int /*<<< orphan*/  MIDL_STUB_MESSAGE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
#define  FC_BOGUS_STRUCT 155 
#define  FC_BYTE 154 
#define  FC_CHAR 153 
#define  FC_CSTRING 152 
#define  FC_CSTRUCT 151 
#define  FC_DOUBLE 150 
#define  FC_ENUM16 149 
#define  FC_ENUM32 148 
#define  FC_FLOAT 147 
#define  FC_HYPER 146 
#define  FC_IP 145 
#define  FC_LGFARRAY 144 
#define  FC_LGVARRAY 143 
#define  FC_LONG 142 
#define  FC_NON_ENCAPSULATED_UNION 141 
#define  FC_PSTRUCT 140 
#define  FC_RANGE 139 
#define  FC_SHORT 138 
#define  FC_SMALL 137 
#define  FC_SMFARRAY 136 
#define  FC_SMVARRAY 135 
#define  FC_STRUCT 134 
#define  FC_ULONG 133 
#define  FC_USER_MARSHAL 132 
#define  FC_USHORT 131 
#define  FC_USMALL 130 
#define  FC_WCHAR 129 
#define  FC_WSTRING 128 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  RPC_X_BAD_STUB_DATA ; 
 int /*<<< orphan*/  RpcRaiseException (int /*<<< orphan*/ ) ; 
 int* SkipConformance (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static ULONG EmbeddedComplexSize(MIDL_STUB_MESSAGE *pStubMsg,
                                 PFORMAT_STRING pFormat)
{
  switch (*pFormat) {
  case FC_STRUCT:
  case FC_PSTRUCT:
  case FC_CSTRUCT:
  case FC_BOGUS_STRUCT:
  case FC_SMFARRAY:
  case FC_SMVARRAY:
  case FC_CSTRING:
    return *(const WORD*)&pFormat[2];
  case FC_LGFARRAY:
  case FC_LGVARRAY:
    return *(const ULONG*)&pFormat[2];
  case FC_USER_MARSHAL:
    return *(const WORD*)&pFormat[4];
  case FC_RANGE: {
    switch (((const NDR_RANGE *)pFormat)->flags_type & 0xf) {
    case FC_BYTE:
    case FC_CHAR:
    case FC_SMALL:
    case FC_USMALL:
        return sizeof(UCHAR);
    case FC_WCHAR:
    case FC_SHORT:
    case FC_USHORT:
        return sizeof(USHORT);
    case FC_LONG:
    case FC_ULONG:
    case FC_ENUM32:
        return sizeof(ULONG);
    case FC_FLOAT:
        return sizeof(float);
    case FC_DOUBLE:
        return sizeof(double);
    case FC_HYPER:
        return sizeof(ULONGLONG);
    case FC_ENUM16:
        return sizeof(UINT);
    default:
        ERR("unknown type 0x%x\n", ((const NDR_RANGE *)pFormat)->flags_type & 0xf);
        RpcRaiseException(RPC_X_BAD_STUB_DATA);
    }
  }
  case FC_NON_ENCAPSULATED_UNION:
    pFormat += 2;
    pFormat = SkipConformance(pStubMsg, pFormat);
    pFormat += *(const SHORT*)pFormat;
    return *(const SHORT*)pFormat;
  case FC_IP:
    return sizeof(void *);
  case FC_WSTRING:
    return *(const WORD*)&pFormat[2] * 2;
  default:
    FIXME("unhandled embedded type %02x\n", *pFormat);
  }
  return 0;
}