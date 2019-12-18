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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  LONGLONG ;
typedef  int /*<<< orphan*/  INT8 ;
typedef  int /*<<< orphan*/  INT64 ;
typedef  int /*<<< orphan*/  INT32 ;
typedef  int /*<<< orphan*/  INT16 ;
typedef  int CIMTYPE ;

/* Variables and functions */
#define  CIM_BOOLEAN 138 
#define  CIM_DATETIME 137 
 int CIM_FLAG_ARRAY ; 
#define  CIM_SINT16 136 
#define  CIM_SINT32 135 
#define  CIM_SINT64 134 
#define  CIM_SINT8 133 
#define  CIM_STRING 132 
#define  CIM_UINT16 131 
#define  CIM_UINT32 130 
#define  CIM_UINT64 129 
#define  CIM_UINT8 128 
 int /*<<< orphan*/  ERR (char*,int) ; 

UINT get_type_size( CIMTYPE type )
{
    if (type & CIM_FLAG_ARRAY) return sizeof(void *);

    switch (type)
    {
    case CIM_BOOLEAN:
        return sizeof(int);
    case CIM_SINT8:
    case CIM_UINT8:
        return sizeof(INT8);
    case CIM_SINT16:
    case CIM_UINT16:
        return sizeof(INT16);
    case CIM_SINT32:
    case CIM_UINT32:
        return sizeof(INT32);
    case CIM_SINT64:
    case CIM_UINT64:
        return sizeof(INT64);
    case CIM_DATETIME:
    case CIM_STRING:
        return sizeof(WCHAR *);
    default:
        ERR("unhandled type %u\n", type);
        break;
    }
    return sizeof(LONGLONG);
}