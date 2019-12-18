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
struct assembly_name {size_t index; int /*<<< orphan*/ * attrs; } ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  struct assembly_name* LPVOID ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 char* MSI_RecordGetString (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msi_alloc (int) ; 
 int /*<<< orphan*/  sprintfW (int /*<<< orphan*/ ,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  strcmpiW (char const*,char const*) ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ ,char const*) ; 
 int strlenW (char const*) ; 

__attribute__((used)) static UINT get_assembly_name_attribute( MSIRECORD *rec, LPVOID param )
{
    static const WCHAR fmtW[] = {'%','s','=','"','%','s','"',0};
    static const WCHAR nameW[] = {'n','a','m','e',0};
    struct assembly_name *name = param;
    const WCHAR *attr = MSI_RecordGetString( rec, 2 );
    const WCHAR *value = MSI_RecordGetString( rec, 3 );
    int len = strlenW( fmtW ) + strlenW( attr ) + strlenW( value );

    if (!(name->attrs[name->index] = msi_alloc( len * sizeof(WCHAR) )))
        return ERROR_OUTOFMEMORY;

    if (!strcmpiW( attr, nameW )) strcpyW( name->attrs[name->index++], value );
    else sprintfW( name->attrs[name->index++], fmtW, attr, value );
    return ERROR_SUCCESS;
}