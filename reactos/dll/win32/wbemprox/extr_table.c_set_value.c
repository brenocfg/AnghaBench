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
struct table {TYPE_1__* columns; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  void* UINT8 ;
typedef  void* UINT64 ;
typedef  void* UINT32 ;
typedef  void* UINT16 ;
typedef  size_t UINT ;
struct TYPE_2__ {int type; } ;
typedef  void* LONGLONG ;
typedef  scalar_t__ INT_PTR ;
typedef  void* INT8 ;
typedef  void* INT64 ;
typedef  void* INT32 ;
typedef  void* INT16 ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int CIMTYPE ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
#define  CIM_DATETIME 137 
#define  CIM_SINT16 136 
#define  CIM_SINT32 135 
#define  CIM_SINT64 134 
#define  CIM_SINT8 133 
#define  CIM_STRING 132 
#define  CIM_UINT16 131 
#define  CIM_UINT32 130 
#define  CIM_UINT64 129 
#define  CIM_UINT8 128 
 int COL_TYPE_MASK ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WBEM_E_FAILED ; 
 int /*<<< orphan*/  WBEM_E_TYPE_MISMATCH ; 
 size_t get_column_offset (struct table const*,size_t) ; 
 size_t get_row_size (struct table const*) ; 

HRESULT set_value( const struct table *table, UINT row, UINT column, LONGLONG val,
                   CIMTYPE type )
{
    UINT col_offset, row_size;
    BYTE *ptr;

    if ((table->columns[column].type & COL_TYPE_MASK) != type) return WBEM_E_TYPE_MISMATCH;

    col_offset = get_column_offset( table, column );
    row_size = get_row_size( table );
    ptr = table->data + row * row_size + col_offset;

    switch (table->columns[column].type & COL_TYPE_MASK)
    {
    case CIM_DATETIME:
    case CIM_STRING:
        *(WCHAR **)ptr = (WCHAR *)(INT_PTR)val;
        break;
    case CIM_SINT8:
        *(INT8 *)ptr = val;
        break;
    case CIM_UINT8:
        *(UINT8 *)ptr = val;
        break;
    case CIM_SINT16:
        *(INT16 *)ptr = val;
        break;
    case CIM_UINT16:
        *(UINT16 *)ptr = val;
        break;
    case CIM_SINT32:
        *(INT32 *)ptr = val;
        break;
    case CIM_UINT32:
        *(UINT32 *)ptr = val;
        break;
    case CIM_SINT64:
        *(INT64 *)ptr = val;
        break;
    case CIM_UINT64:
        *(UINT64 *)ptr = val;
        break;
    default:
        FIXME("unhandled column type %u\n", type);
        return WBEM_E_FAILED;
    }
    return S_OK;
}