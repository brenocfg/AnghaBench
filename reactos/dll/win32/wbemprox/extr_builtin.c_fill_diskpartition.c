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
struct table {int data; int num_rows; } ;
struct record_diskpartition {int bootable; int bootpartition; int diskindex; int size; int /*<<< orphan*/  type; scalar_t__ startingoffset; void* pnpdevice_id; scalar_t__ index; void* device_id; } ;
struct expr {int dummy; } ;
typedef  enum fill_status { ____Placeholder_fill_status } fill_status ;
typedef  char WCHAR ;
typedef  int UINT64 ;
typedef  int UINT ;
typedef  int DWORD ;

/* Variables and functions */
 int DRIVE_FIXED ; 
 int DRIVE_REMOVABLE ; 
 int FILL_STATUS_FAILED ; 
 int FILL_STATUS_UNFILTERED ; 
 int GetDriveTypeW (char*) ; 
 int GetLogicalDrives () ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  free_row_values (struct table*,int) ; 
 int /*<<< orphan*/  get_filesystem (char*) ; 
 int /*<<< orphan*/  get_freespace (char*,int*) ; 
 void* heap_strdupW (char*) ; 
 int /*<<< orphan*/  match_row (struct table*,int,struct expr const*,int*) ; 
 int /*<<< orphan*/  resize_table (struct table*,int,int) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,int) ; 

__attribute__((used)) static enum fill_status fill_diskpartition( struct table *table, const struct expr *cond )
{
    static const WCHAR fmtW[] =
        {'D','i','s','k',' ','#','%','u',',',' ','P','a','r','t','i','t','i','o','n',' ','#','0',0};
    WCHAR device_id[32], root[] = {'A',':','\\',0};
    struct record_diskpartition *rec;
    UINT i, row = 0, offset = 0, type, index = 0;
    UINT64 size = 1024 * 1024 * 1024;
    DWORD drives = GetLogicalDrives();
    enum fill_status status = FILL_STATUS_UNFILTERED;

    if (!resize_table( table, 4, sizeof(*rec) )) return FILL_STATUS_FAILED;

    for (i = 0; i < 26; i++)
    {
        if (drives & (1 << i))
        {
            root[0] = 'A' + i;
            type = GetDriveTypeW( root );
            if (type != DRIVE_FIXED && type != DRIVE_REMOVABLE)
                continue;

            if (!resize_table( table, row + 1, sizeof(*rec) )) return FILL_STATUS_FAILED;

            rec = (struct record_diskpartition *)(table->data + offset);
            rec->bootable       = (i == 2) ? -1 : 0;
            rec->bootpartition  = (i == 2) ? -1 : 0;
            sprintfW( device_id, fmtW, index );
            rec->device_id      = heap_strdupW( device_id );
            rec->diskindex      = index;
            rec->index          = 0;
            rec->pnpdevice_id   = heap_strdupW( device_id );
            get_freespace( root, &size );
            rec->size           = size;
            rec->startingoffset = 0;
            rec->type           = get_filesystem( root );
            if (!match_row( table, row, cond, &status ))
            {
                free_row_values( table, row );
                continue;
            }
            offset += sizeof(*rec);
            row++;
            index++;
        }
    }
    TRACE("created %u rows\n", row);
    table->num_rows = row;
    return status;
}