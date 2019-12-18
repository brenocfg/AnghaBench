#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct msi_primary_key_record_info {TYPE_1__* rec; scalar_t__ n; } ;
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_8__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_7__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIRECORD ;
typedef  TYPE_2__ MSIQUERY ;
typedef  int /*<<< orphan*/  MSIDATABASE ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_TABLE ; 
 scalar_t__ ERROR_SUCCESS ; 
 TYPE_1__* MSI_CreateRecord (scalar_t__) ; 
 scalar_t__ MSI_IterateRecords (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct msi_primary_key_record_info*) ; 
 scalar_t__ MSI_OpenQuery (int /*<<< orphan*/ *,TYPE_2__**,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TABLE_Exists (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  msi_primary_key_iterator ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

UINT MSI_DatabaseGetPrimaryKeys( MSIDATABASE *db,
                LPCWSTR table, MSIRECORD **prec )
{
    static const WCHAR sql[] = {
        's','e','l','e','c','t',' ','*',' ',
        'f','r','o','m',' ','`','_','C','o','l','u','m','n','s','`',' ',
        'w','h','e','r','e',' ',
        '`','T','a','b','l','e','`',' ','=',' ','\'','%','s','\'',0 };
    struct msi_primary_key_record_info info;
    MSIQUERY *query = NULL;
    UINT r;

    if (!TABLE_Exists( db, table ))
        return ERROR_INVALID_TABLE;

    r = MSI_OpenQuery( db, &query, sql, table );
    if( r != ERROR_SUCCESS )
        return r;

    /* count the number of primary key records */
    info.n = 0;
    info.rec = 0;
    r = MSI_IterateRecords( query, 0, msi_primary_key_iterator, &info );
    if( r == ERROR_SUCCESS )
    {
        TRACE("Found %d primary keys\n", info.n );

        /* allocate a record and fill in the names of the tables */
        info.rec = MSI_CreateRecord( info.n );
        info.n = 0;
        r = MSI_IterateRecords( query, 0, msi_primary_key_iterator, &info );
        if( r == ERROR_SUCCESS )
            *prec = info.rec;
        else
            msiobj_release( &info.rec->hdr );
    }
    msiobj_release( &query->hdr );

    return r;
}