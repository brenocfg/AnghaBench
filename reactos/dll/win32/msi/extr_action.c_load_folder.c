#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_9__ {int /*<<< orphan*/  entry; void* SourceShortPath; void* SourceLongPath; void* TargetDefault; void* Directory; void* Parent; int /*<<< orphan*/  children; } ;
struct TYPE_8__ {int /*<<< orphan*/  folders; } ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  TYPE_2__ MSIFOLDER ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  TYPE_1__* LPVOID ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (void*) ; 
 int /*<<< orphan*/ * folder_split_path (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_folder_persistence (TYPE_1__*,TYPE_2__*) ; 
 TYPE_2__* msi_alloc_zero (int) ; 
 void* msi_dup_record_field (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* strdupW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  szDot ; 

__attribute__((used)) static UINT load_folder( MSIRECORD *row, LPVOID param )
{
    MSIPACKAGE *package = param;
    static WCHAR szEmpty[] = { 0 };
    LPWSTR p, tgt_short, tgt_long, src_short, src_long;
    MSIFOLDER *folder;

    if (!(folder = msi_alloc_zero( sizeof(*folder) ))) return ERROR_NOT_ENOUGH_MEMORY;
    list_init( &folder->children );
    folder->Directory = msi_dup_record_field( row, 1 );
    folder->Parent = msi_dup_record_field( row, 2 );
    p = msi_dup_record_field(row, 3);

    TRACE("%s\n", debugstr_w(folder->Directory));

    /* split src and target dir */
    tgt_short = p;
    src_short = folder_split_path( p, ':' );

    /* split the long and short paths */
    tgt_long = folder_split_path( tgt_short, '|' );
    src_long = folder_split_path( src_short, '|' );

    /* check for no-op dirs */
    if (tgt_short && !strcmpW( szDot, tgt_short ))
        tgt_short = szEmpty;
    if (src_short && !strcmpW( szDot, src_short ))
        src_short = szEmpty;

    if (!tgt_long)
        tgt_long = tgt_short;

    if (!src_short) {
        src_short = tgt_short;
        src_long = tgt_long;
    }

    if (!src_long)
        src_long = src_short;

    /* FIXME: use the target short path too */
    folder->TargetDefault = strdupW(tgt_long);
    folder->SourceShortPath = strdupW(src_short);
    folder->SourceLongPath = strdupW(src_long);
    msi_free(p);

    TRACE("TargetDefault = %s\n",debugstr_w( folder->TargetDefault ));
    TRACE("SourceLong = %s\n", debugstr_w( folder->SourceLongPath ));
    TRACE("SourceShort = %s\n", debugstr_w( folder->SourceShortPath ));

    load_folder_persistence( package, folder );

    list_add_tail( &package->folders, &folder->entry );
    return ERROR_SUCCESS;
}