#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_10__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_9__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIRECORD ;
typedef  TYPE_2__ MSIQUERY ;
typedef  int /*<<< orphan*/  MSIDATABASE ;
typedef  int /*<<< orphan*/  IStream ;

/* Variables and functions */
 scalar_t__ ERROR_OUTOFMEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 TYPE_1__* MSI_CreateRecord (int) ; 
 scalar_t__ MSI_DatabaseOpenViewW (int /*<<< orphan*/ *,char const*,TYPE_2__**) ; 
 scalar_t__ MSI_RecordSetIStream (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ MSI_RecordSetStringW (TYPE_1__*,int,char const*) ; 
 scalar_t__ MSI_ViewExecute (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_w (char const*) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT add_stream( MSIDATABASE *db, const WCHAR *name, IStream *data )
{
    static const WCHAR insert[] = {
        'I','N','S','E','R','T',' ','I','N','T','O',' ',
        '`','_','S','t','r','e','a','m','s','`',' ',
        '(','`','N','a','m','e','`',',','`','D','a','t','a','`',')',' ',
        'V','A','L','U','E','S',' ','(','?',',','?',')',0};
    static const WCHAR update[] = {
        'U','P','D','A','T','E',' ','`','_','S','t','r','e','a','m','s','`',' ',
        'S','E','T',' ','`','D','a','t','a','`',' ','=',' ','?',' ',
        'W','H','E','R','E',' ','`','N','a','m','e','`',' ','=',' ','?',0};
    MSIQUERY *query;
    MSIRECORD *rec;
    UINT r;

    TRACE("%p %s %p\n", db, debugstr_w(name), data);

    if (!(rec = MSI_CreateRecord( 2 )))
        return ERROR_OUTOFMEMORY;

    r = MSI_RecordSetStringW( rec, 1, name );
    if (r != ERROR_SUCCESS)
       goto done;

    r = MSI_RecordSetIStream( rec, 2, data );
    if (r != ERROR_SUCCESS)
       goto done;

    r = MSI_DatabaseOpenViewW( db, insert, &query );
    if (r != ERROR_SUCCESS)
       goto done;

    r = MSI_ViewExecute( query, rec );
    msiobj_release( &query->hdr );
    if (r == ERROR_SUCCESS)
        goto done;

    msiobj_release( &rec->hdr );
    if (!(rec = MSI_CreateRecord( 2 )))
        return ERROR_OUTOFMEMORY;

    r = MSI_RecordSetIStream( rec, 1, data );
    if (r != ERROR_SUCCESS)
       goto done;

    r = MSI_RecordSetStringW( rec, 2, name );
    if (r != ERROR_SUCCESS)
       goto done;

    r = MSI_DatabaseOpenViewW( db, update, &query );
    if (r != ERROR_SUCCESS)
        goto done;

    r = MSI_ViewExecute( query, rec );
    msiobj_release( &query->hdr );

done:
    msiobj_release( &rec->hdr );
    return r;
}