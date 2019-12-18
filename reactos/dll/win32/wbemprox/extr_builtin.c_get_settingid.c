#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  guid ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_4__ {int /*<<< orphan*/  Data1; } ;
typedef  TYPE_1__ GUID ;

/* Variables and functions */
 int /*<<< orphan*/  RpcStringFreeW (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  UuidToStringW (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * heap_strdupW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static WCHAR *get_settingid( UINT32 index )
{
    GUID guid;
    WCHAR *ret, *str;
    memset( &guid, 0, sizeof(guid) );
    guid.Data1 = index;
    UuidToStringW( &guid, &str );
    ret = heap_strdupW( str );
    RpcStringFreeW( &str );
    return ret;
}