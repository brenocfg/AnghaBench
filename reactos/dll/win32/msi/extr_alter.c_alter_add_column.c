#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_18__ {int hold; TYPE_1__* colinfo; int /*<<< orphan*/  db; } ;
struct TYPE_17__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_16__ {TYPE_2__* ops; } ;
struct TYPE_15__ {scalar_t__ (* add_column ) (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* delete ) (TYPE_3__*) ;} ;
struct TYPE_14__ {int /*<<< orphan*/  type; int /*<<< orphan*/  column; int /*<<< orphan*/  table; } ;
typedef  TYPE_3__ MSIVIEW ;
typedef  TYPE_4__ MSIQUERY ;
typedef  TYPE_5__ MSIALTERVIEW ;

/* Variables and functions */
 scalar_t__ ERROR_BAD_QUERY_SYNTAX ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  ITERATE_columns ; 
 scalar_t__ MSI_IterateRecords (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ MSI_OpenQuery (int /*<<< orphan*/ ,TYPE_4__**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TABLE_CreateView (int /*<<< orphan*/ ,char const*,TYPE_3__**) ; 
 scalar_t__ check_column_exists (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 
 scalar_t__ stub3 (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__*) ; 

__attribute__((used)) static UINT alter_add_column(MSIALTERVIEW *av)
{
    UINT r, colnum = 1;
    MSIQUERY *view;
    MSIVIEW *columns;

    static const WCHAR szColumns[] = {'_','C','o','l','u','m','n','s',0};
    static const WCHAR query[] = {
        'S','E','L','E','C','T',' ','*',' ','F','R','O','M',' ',
        '`','_','C','o','l','u','m','n','s','`',' ','W','H','E','R','E',' ',
        '`','T','a','b','l','e','`','=','\'','%','s','\'',' ','O','R','D','E','R',' ',
        'B','Y',' ','`','N','u','m','b','e','r','`',0
    };

    r = TABLE_CreateView(av->db, szColumns, &columns);
    if (r != ERROR_SUCCESS)
        return r;

    if (check_column_exists(av->db, av->colinfo->table, av->colinfo->column))
    {
        columns->ops->delete(columns);
        return ERROR_BAD_QUERY_SYNTAX;
    }

    r = MSI_OpenQuery(av->db, &view, query, av->colinfo->table, av->colinfo->column);
    if (r == ERROR_SUCCESS)
    {
        r = MSI_IterateRecords(view, NULL, ITERATE_columns, &colnum);
        msiobj_release(&view->hdr);
        if (r != ERROR_SUCCESS)
        {
            columns->ops->delete(columns);
            return r;
        }
    }
    r = columns->ops->add_column(columns, av->colinfo->table,
                                 colnum, av->colinfo->column,
                                 av->colinfo->type, (av->hold == 1));

    columns->ops->delete(columns);
    return r;
}