#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct data_block {scalar_t__ compressed; scalar_t__ uncompressed; int /*<<< orphan*/  entry; } ;
struct TYPE_10__ {int handle; } ;
struct TYPE_8__ {scalar_t__ cbReserveCFData; } ;
struct TYPE_9__ {scalar_t__ (* compress ) (TYPE_2__*) ;scalar_t__ (* write ) (int,int /*<<< orphan*/ ,scalar_t__,int*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  pv; int /*<<< orphan*/  blocks_list; int /*<<< orphan*/  cDataBlocks; int /*<<< orphan*/  cCompressedBytesInFolder; TYPE_1__ ccab; int /*<<< orphan*/  pending_data_size; scalar_t__ cdata_in; int /*<<< orphan*/  (* free ) (struct data_block*) ;int /*<<< orphan*/  data_out; TYPE_6__ data; struct data_block* (* alloc ) (int) ;} ;
typedef  int (* PFNFCISTATUS ) (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ;
typedef  TYPE_2__ FCI_Int ;
typedef  int /*<<< orphan*/  CFDATA ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ERROR_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FCIERR_ALLOC_FAIL ; 
 int /*<<< orphan*/  FCIERR_TEMP_FILE ; 
 int /*<<< orphan*/  FCIERR_USER_ABORT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  create_temp_file (TYPE_2__*,TYPE_6__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_error (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  statusFile ; 
 struct data_block* stub1 (int) ; 
 scalar_t__ stub2 (TYPE_2__*) ; 
 scalar_t__ stub3 (int,int /*<<< orphan*/ ,scalar_t__,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct data_block*) ; 

__attribute__((used)) static BOOL add_data_block( FCI_Int *fci, PFNFCISTATUS status_callback )
{
    int err;
    struct data_block *block;

    if (!fci->cdata_in) return TRUE;

    if (fci->data.handle == -1 && !create_temp_file( fci, &fci->data )) return FALSE;

    if (!(block = fci->alloc( sizeof(*block) )))
    {
        set_error( fci, FCIERR_ALLOC_FAIL, ERROR_NOT_ENOUGH_MEMORY );
        return FALSE;
    }
    block->uncompressed = fci->cdata_in;
    block->compressed   = fci->compress( fci );

    if (fci->write( fci->data.handle, fci->data_out,
                    block->compressed, &err, fci->pv ) != block->compressed)
    {
        set_error( fci, FCIERR_TEMP_FILE, err );
        fci->free( block );
        return FALSE;
    }

    fci->cdata_in = 0;
    fci->pending_data_size += sizeof(CFDATA) + fci->ccab.cbReserveCFData + block->compressed;
    fci->cCompressedBytesInFolder += block->compressed;
    fci->cDataBlocks++;
    list_add_tail( &fci->blocks_list, &block->entry );

    if (status_callback( statusFile, block->compressed, block->uncompressed, fci->pv ) == -1)
    {
        set_error( fci, FCIERR_USER_ABORT, 0 );
        return FALSE;
    }
    return TRUE;
}