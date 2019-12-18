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
struct table {int data; int num_rows; } ;
struct record_process {int /*<<< orphan*/  get_owner; scalar_t__ workingsetsize; int /*<<< orphan*/  thread_count; int /*<<< orphan*/  pprocess_id; int /*<<< orphan*/  process_id; void* name; void* handle; void* description; int /*<<< orphan*/  commandline; void* caption; } ;
struct expr {int dummy; } ;
typedef  enum fill_status { ____Placeholder_fill_status } fill_status ;
typedef  int /*<<< orphan*/  entry ;
typedef  char WCHAR ;
typedef  int UINT ;
struct TYPE_4__ {int dwSize; char* szExeFile; int /*<<< orphan*/  cntThreads; int /*<<< orphan*/  th32ParentProcessID; int /*<<< orphan*/  th32ProcessID; } ;
typedef  TYPE_1__ PROCESSENTRY32W ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateToolhelp32Snapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FILL_STATUS_FAILED ; 
 int FILL_STATUS_UNFILTERED ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  Process32FirstW (scalar_t__,TYPE_1__*) ; 
 scalar_t__ Process32NextW (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  TH32CS_SNAPPROCESS ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  free_row_values (struct table*,int) ; 
 int /*<<< orphan*/  get_cmdline (int /*<<< orphan*/ ) ; 
 void* heap_strdupW (char*) ; 
 int /*<<< orphan*/  match_row (struct table*,int,struct expr const*,int*) ; 
 int /*<<< orphan*/  process_get_owner ; 
 int /*<<< orphan*/  resize_table (struct table*,int,int) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum fill_status fill_process( struct table *table, const struct expr *cond )
{
    static const WCHAR fmtW[] = {'%','u',0};
    WCHAR handle[11];
    struct record_process *rec;
    PROCESSENTRY32W entry;
    HANDLE snap;
    enum fill_status status = FILL_STATUS_FAILED;
    UINT row = 0, offset = 0;

    snap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
    if (snap == INVALID_HANDLE_VALUE) return FILL_STATUS_FAILED;

    entry.dwSize = sizeof(entry);
    if (!Process32FirstW( snap, &entry )) goto done;
    if (!resize_table( table, 8, sizeof(*rec) )) goto done;

    do
    {
        if (!resize_table( table, row + 1, sizeof(*rec) )) goto done;

        rec = (struct record_process *)(table->data + offset);
        rec->caption        = heap_strdupW( entry.szExeFile );
        rec->commandline    = get_cmdline( entry.th32ProcessID );
        rec->description    = heap_strdupW( entry.szExeFile );
        sprintfW( handle, fmtW, entry.th32ProcessID );
        rec->handle         = heap_strdupW( handle );
        rec->name           = heap_strdupW( entry.szExeFile );
        rec->process_id     = entry.th32ProcessID;
        rec->pprocess_id    = entry.th32ParentProcessID;
        rec->thread_count   = entry.cntThreads;
        rec->workingsetsize = 0;
        rec->get_owner      = process_get_owner;
        if (!match_row( table, row, cond, &status ))
        {
            free_row_values( table, row );
            continue;
        }
        offset += sizeof(*rec);
        row++;
    } while (Process32NextW( snap, &entry ));

    TRACE("created %u rows\n", row);
    table->num_rows = row;
    status = FILL_STATUS_UNFILTERED;

done:
    CloseHandle( snap );
    return status;
}