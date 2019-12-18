#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct file {int size; int /*<<< orphan*/  attribs; int /*<<< orphan*/  time; int /*<<< orphan*/  date; } ;
struct TYPE_7__ {int (* read ) (int,scalar_t__,scalar_t__,int*,int /*<<< orphan*/ ) ;scalar_t__ data_in; scalar_t__ cdata_in; int /*<<< orphan*/  pv; int /*<<< orphan*/  (* close ) (int,int*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  PFNFCISTATUS ;
typedef  int (* PFNFCIGETOPENINFO ) (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ;
typedef  int INT_PTR ;
typedef  TYPE_1__ FCI_Int ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CAB_BLOCKMAX ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FCIERR_OPEN_SRC ; 
 int /*<<< orphan*/  FCIERR_READ_SRC ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _A_EXEC ; 
 int /*<<< orphan*/  add_data_block (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct file* add_file (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  free_file (TYPE_1__*,struct file*) ; 
 int /*<<< orphan*/  set_error (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int stub1 (int,scalar_t__,scalar_t__,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL add_file_data( FCI_Int *fci, char *sourcefile, char *filename, BOOL execute,
                           PFNFCIGETOPENINFO get_open_info, PFNFCISTATUS status_callback )
{
    int err, len;
    INT_PTR handle;
    struct file *file;

    if (!(file = add_file( fci, filename ))) return FALSE;

    handle = get_open_info( sourcefile, &file->date, &file->time, &file->attribs, &err, fci->pv );
    if (handle == -1)
    {
        free_file( fci, file );
        set_error( fci, FCIERR_OPEN_SRC, err );
        return FALSE;
    }
    if (execute) file->attribs |= _A_EXEC;

    for (;;)
    {
        len = fci->read( handle, fci->data_in + fci->cdata_in,
                         CAB_BLOCKMAX - fci->cdata_in, &err, fci->pv );
        if (!len) break;

        if (len == -1)
        {
            set_error( fci, FCIERR_READ_SRC, err );
            return FALSE;
        }
        file->size += len;
        fci->cdata_in += len;
        if (fci->cdata_in == CAB_BLOCKMAX && !add_data_block( fci, status_callback )) return FALSE;
    }
    fci->close( handle, &err, fci->pv );
    return TRUE;
}