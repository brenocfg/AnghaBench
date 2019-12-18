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
typedef  int UINT8 ;
typedef  int UINT64 ;
typedef  int UINT32 ;
typedef  int UINT16 ;
typedef  int UINT ;
struct TYPE_2__ {int type; } ;
typedef  int LONGLONG ;
typedef  int INT_PTR ;
typedef  int INT8 ;
typedef  int INT64 ;
typedef  int INT32 ;
typedef  int INT16 ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BYTE ;

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
 int COL_TYPE_MASK ; 
 int /*<<< orphan*/  ERR (char*,int) ; 
 int /*<<< orphan*/  S_OK ; 
 int get_column_offset (struct table const*,int) ; 
 int get_row_size (struct table const*) ; 

HRESULT get_value( const struct table *table, UINT row, UINT column, LONGLONG *val )
{
    UINT col_offset, row_size;
    const BYTE *ptr;

    col_offset = get_column_offset( table, column );
    row_size = get_row_size( table );
    ptr = table->data + row * row_size + col_offset;

    if (table->columns[column].type & CIM_FLAG_ARRAY)
    {
        *val = (INT_PTR)*(const void **)ptr;
        return S_OK;
    }
    switch (table->columns[column].type & COL_TYPE_MASK)
    {
    case CIM_BOOLEAN:
        *val = *(const int *)ptr;
        break;
    case CIM_DATETIME:
    case CIM_STRING:
        *val = (INT_PTR)*(const WCHAR **)ptr;
        break;
    case CIM_SINT8:
        *val = *(const INT8 *)ptr;
        break;
    case CIM_UINT8:
        *val = *(const UINT8 *)ptr;
        break;
    case CIM_SINT16:
        *val = *(const INT16 *)ptr;
        break;
    case CIM_UINT16:
        *val = *(const UINT16 *)ptr;
        break;
    case CIM_SINT32:
        *val = *(const INT32 *)ptr;
        break;
    case CIM_UINT32:
        *val = *(const UINT32 *)ptr;
        break;
    case CIM_SINT64:
        *val = *(const INT64 *)ptr;
        break;
    case CIM_UINT64:
        *val = *(const UINT64 *)ptr;
        break;
    default:
        ERR("invalid column type %u\n", table->columns[column].type & COL_TYPE_MASK);
        *val = 0;
        break;
    }
    return S_OK;
}