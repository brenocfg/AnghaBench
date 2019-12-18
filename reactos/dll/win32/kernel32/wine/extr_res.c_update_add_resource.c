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
struct resource_dir_entry {int /*<<< orphan*/  children; void* id; } ;
struct resource_data {int /*<<< orphan*/  entry; } ;
struct TYPE_4__ {int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ QUEUEDUPDATES ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  LANGID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 struct resource_dir_entry* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource_data*) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  add_resource_data_entry (int /*<<< orphan*/ *,struct resource_data*) ; 
 int /*<<< orphan*/  add_resource_dir_entry (int /*<<< orphan*/ *,struct resource_dir_entry*) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 struct resource_data* find_resource_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct resource_dir_entry* find_resource_dir_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 
 void* res_strdupW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL update_add_resource( QUEUEDUPDATES *updates, LPCWSTR Type, LPCWSTR Name,
                                 LANGID Lang, struct resource_data *resdata,
                                 BOOL overwrite_existing )
{
    struct resource_dir_entry *restype, *resname;
    struct resource_data *existing;

    TRACE("%p %s %s %p %d\n", updates,
          debugstr_w(Type), debugstr_w(Name), resdata, overwrite_existing );

    restype = find_resource_dir_entry( &updates->root, Type );
    if (!restype)
    {
        restype = HeapAlloc( GetProcessHeap(), 0, sizeof *restype );
        restype->id = res_strdupW( Type );
        list_init( &restype->children );
        add_resource_dir_entry( &updates->root, restype );
    }

    resname = find_resource_dir_entry( &restype->children, Name );
    if (!resname)
    {
        resname = HeapAlloc( GetProcessHeap(), 0, sizeof *resname );
        resname->id = res_strdupW( Name );
        list_init( &resname->children );
        add_resource_dir_entry( &restype->children, resname );
    }

    /*
     * If there's an existing resource entry with matching (Type,Name,Language)
     *  it needs to be removed before adding the new data.
     */
    existing = find_resource_data( &resname->children, Lang );
    if (existing)
    {
        if (!overwrite_existing)
            return FALSE;
        list_remove( &existing->entry );
        HeapFree( GetProcessHeap(), 0, existing );
    }

    if (resdata)
        add_resource_data_entry( &resname->children, resdata );

    return TRUE;
}