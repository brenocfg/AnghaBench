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
struct table {TYPE_1__* columns; } ;
typedef  char WCHAR ;
typedef  size_t UINT ;
struct TYPE_2__ {int type; } ;
typedef  char const* LONGLONG ;
typedef  scalar_t__ INT_PTR ;
typedef  char* BSTR ;

/* Variables and functions */
#define  CIM_BOOLEAN 136 
#define  CIM_DATETIME 135 
 int CIM_FLAG_ARRAY ; 
#define  CIM_SINT16 134 
#define  CIM_SINT32 133 
#define  CIM_SINT64 132 
#define  CIM_STRING 131 
#define  CIM_UINT16 130 
#define  CIM_UINT32 129 
#define  CIM_UINT64 128 
 int COL_TYPE_MASK ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 scalar_t__ S_OK ; 
 char* SysAllocString (char const*) ; 
 char* SysAllocStringLen (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ get_value (struct table const*,size_t,size_t,char const**) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,char const*) ; 
 int /*<<< orphan*/  strlenW (char const*) ; 
 int /*<<< orphan*/  wsprintfW (char*,char const*,char const*) ; 

BSTR get_value_bstr( const struct table *table, UINT row, UINT column )
{
    static const WCHAR fmt_signedW[] = {'%','d',0};
    static const WCHAR fmt_unsignedW[] = {'%','u',0};
    static const WCHAR fmt_signed64W[] = {'%','I','6','4','d',0};
    static const WCHAR fmt_unsigned64W[] = {'%','I','6','4','u',0};
    static const WCHAR fmt_strW[] = {'\"','%','s','\"',0};
    static const WCHAR trueW[] = {'T','R','U','E',0};
    static const WCHAR falseW[] = {'F','A','L','S','E',0};
    LONGLONG val;
    BSTR ret;
    WCHAR number[22];
    UINT len;

    if (table->columns[column].type & CIM_FLAG_ARRAY)
    {
        FIXME("array to string conversion not handled\n");
        return NULL;
    }
    if (get_value( table, row, column, &val ) != S_OK) return NULL;

    switch (table->columns[column].type & COL_TYPE_MASK)
    {
    case CIM_BOOLEAN:
        if (val) return SysAllocString( trueW );
        else return SysAllocString( falseW );

    case CIM_DATETIME:
    case CIM_STRING:
        if (!val) return NULL;
        len = strlenW( (const WCHAR *)(INT_PTR)val ) + 2;
        if (!(ret = SysAllocStringLen( NULL, len ))) return NULL;
        sprintfW( ret, fmt_strW, (const WCHAR *)(INT_PTR)val );
        return ret;

    case CIM_SINT16:
    case CIM_SINT32:
        sprintfW( number, fmt_signedW, val );
        return SysAllocString( number );

    case CIM_UINT16:
    case CIM_UINT32:
        sprintfW( number, fmt_unsignedW, val );
        return SysAllocString( number );

    case CIM_SINT64:
        wsprintfW( number, fmt_signed64W, val );
        return SysAllocString( number );

    case CIM_UINT64:
        wsprintfW( number, fmt_unsigned64W, val );
        return SysAllocString( number );

    default:
        FIXME("unhandled column type %u\n", table->columns[column].type & COL_TYPE_MASK);
        break;
    }
    return NULL;
}