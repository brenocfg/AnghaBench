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
struct tagMSIVIEW {int dummy; } ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int MAX_STORAGES_NAME_LEN ; 
 int MSITYPE_NULLABLE ; 
 int MSITYPE_STRING ; 
 int MSITYPE_VALID ; 
 int NUM_STORAGES_COLS ; 
 int /*<<< orphan*/  TRACE (char*,struct tagMSIVIEW*,int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  szData ; 
 int /*<<< orphan*/  szName ; 
 int /*<<< orphan*/  szStorages ; 

__attribute__((used)) static UINT STORAGES_get_column_info( struct tagMSIVIEW *view, UINT n, LPCWSTR *name,
                                      UINT *type, BOOL *temporary, LPCWSTR *table_name )
{
    TRACE("(%p, %d, %p, %p, %p, %p)\n", view, n, name, type, temporary,
          table_name);

    if (n == 0 || n > NUM_STORAGES_COLS)
        return ERROR_INVALID_PARAMETER;

    switch (n)
    {
    case 1:
        if (name) *name = szName;
        if (type) *type = MSITYPE_STRING | MSITYPE_VALID | MAX_STORAGES_NAME_LEN;
        break;

    case 2:
        if (name) *name = szData;
        if (type) *type = MSITYPE_STRING | MSITYPE_VALID | MSITYPE_NULLABLE;
        break;
    }
    if (table_name) *table_name = szStorages;
    if (temporary) *temporary = FALSE;
    return ERROR_SUCCESS;
}