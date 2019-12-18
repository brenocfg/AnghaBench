#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ cab_ULONG ;
struct TYPE_11__ {scalar_t__ cbReserveCFFolder; scalar_t__ cb; scalar_t__ cbFolderThresh; int /*<<< orphan*/  szDisk; int /*<<< orphan*/  szCab; int /*<<< orphan*/  iCab; } ;
struct TYPE_12__ {scalar_t__ files_size; scalar_t__ fNextCab; scalar_t__ folders_size; scalar_t__ placed_files_size; scalar_t__ pending_data_size; scalar_t__ folders_data_size; scalar_t__ fGetNextCabInVain; scalar_t__ cCompressedBytesInFolder; scalar_t__ fNewPrevious; TYPE_1__ ccab; int /*<<< orphan*/  pv; int /*<<< orphan*/  estimatedCabinetSize; TYPE_1__* pccab; int /*<<< orphan*/  statusFolderTotal; int /*<<< orphan*/  szPrevDisk; int /*<<< orphan*/  szPrevCab; scalar_t__ fPrevCab; scalar_t__ fSplitFolder; } ;
typedef  int /*<<< orphan*/  PFNFCISTATUS ;
typedef  int /*<<< orphan*/  (* PFNFCIGETNEXTCABINET ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
typedef  TYPE_2__ FCI_Int ;
typedef  int /*<<< orphan*/  CFFOLDER ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CB_MAX_CABINET_NAME ; 
 scalar_t__ CB_MAX_DISK_NAME ; 
 int /*<<< orphan*/  ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  ERROR_GEN_FAILURE ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FCIERR_NONE ; 
 scalar_t__ TRUE ; 
 scalar_t__ fci_flush_folder (TYPE_2__*,scalar_t__,int /*<<< orphan*/  (*) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ),int /*<<< orphan*/ ) ; 
 scalar_t__ get_header_size (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_error (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_cabinet (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL fci_flush_cabinet( FCI_Int *p_fci_internal,
	BOOL                  fGetNextCab,
	PFNFCIGETNEXTCABINET  pfnfcignc,
	PFNFCISTATUS          pfnfcis)
{
  cab_ULONG read_result=0;
  BOOL returntrue=FALSE;

  /* TODO test if fci_flush_cabinet really aborts if there was no FCIAddFile */

  /* when FCIFlushCabinet was or FCIAddFile hasn't been called */
  if( p_fci_internal->files_size==0 && fGetNextCab ) {
    returntrue=TRUE;
  }

  if (!fci_flush_folder(p_fci_internal,fGetNextCab,pfnfcignc,pfnfcis)){
    /* TODO set error */
    return FALSE;
  }

  if(returntrue) return TRUE;

  if ( (p_fci_internal->fSplitFolder && p_fci_internal->fNextCab==FALSE)||
       (p_fci_internal->folders_size==0 &&
         (p_fci_internal->files_size!=0 ||
          p_fci_internal->placed_files_size!=0 )
     ) )
  {
      /* error */
      set_error( p_fci_internal, FCIERR_NONE, ERROR_GEN_FAILURE );
      return FALSE;
  }

  /* create the cabinet */
  if (!write_cabinet( p_fci_internal, pfnfcis )) return FALSE;

  p_fci_internal->fPrevCab=TRUE;
  /* The sections szPrevCab and szPrevDisk are not being updated, because */
  /* MS CABINET.DLL always puts the first cabinet name and disk into them */

  if (p_fci_internal->fNextCab) {
    p_fci_internal->fNextCab=FALSE;

    if (p_fci_internal->files_size==0 && p_fci_internal->pending_data_size!=0) {
      /* THIS CAN NEVER HAPPEN */
      /* set error code */
      set_error( p_fci_internal, FCIERR_NONE, ERROR_GEN_FAILURE );
      return FALSE;
    }

    if( p_fci_internal->fNewPrevious ) {
      memcpy(p_fci_internal->szPrevCab, p_fci_internal->ccab.szCab,
        CB_MAX_CABINET_NAME);
      memcpy(p_fci_internal->szPrevDisk, p_fci_internal->ccab.szDisk,
        CB_MAX_DISK_NAME);
      p_fci_internal->fNewPrevious=FALSE;
    }
    p_fci_internal->ccab = *p_fci_internal->pccab;

    /* REUSE the variable read_result */
    read_result=get_header_size( p_fci_internal );
    if(p_fci_internal->files_size!=0) {
        read_result+=p_fci_internal->ccab.cbReserveCFFolder;
    }
    read_result+= p_fci_internal->pending_data_size +
      p_fci_internal->files_size + p_fci_internal->folders_data_size +
      p_fci_internal->placed_files_size + p_fci_internal->folders_size +
      sizeof(CFFOLDER); /* set size of new CFFolder entry */

    /* too much data for the maximum size of a cabinet */
    if( p_fci_internal->fGetNextCabInVain==FALSE &&
        p_fci_internal->ccab.cb < read_result ) {
      return fci_flush_cabinet( p_fci_internal, FALSE, pfnfcignc, pfnfcis);
    }

    /* Might be too much data for the maximum size of a cabinet.*/
    /* When any further data will be added later, it might not */
    /* be possible to flush the cabinet, because there might */
    /* not be enough space to store the name of the following */
    /* cabinet and name of the corresponding disk. */
    /* So take care of this and get the name of the next cabinet */
    if (p_fci_internal->fGetNextCabInVain==FALSE && (
      p_fci_internal->ccab.cb < read_result +
      CB_MAX_CABINET_NAME + CB_MAX_DISK_NAME
    )) {
      /* increment cabinet index */
      ++(p_fci_internal->pccab->iCab);
      /* get name of next cabinet */
      p_fci_internal->estimatedCabinetSize=p_fci_internal->statusFolderTotal;
      if (!(*pfnfcignc)(p_fci_internal->pccab,
          p_fci_internal->estimatedCabinetSize, /* estimated size of cab */
          p_fci_internal->pv)) {
        /* error handling */
        set_error( p_fci_internal, FCIERR_NONE, ERROR_FUNCTION_FAILED );
        return FALSE;
      }
      /* Skip a few lines of code. This is caught by the next if. */
      p_fci_internal->fGetNextCabInVain=TRUE;
    }

    /* too much data for cabinet */
    if (p_fci_internal->fGetNextCabInVain && (
        p_fci_internal->ccab.cb < read_result +
        strlen(p_fci_internal->ccab.szCab)+1+
        strlen(p_fci_internal->ccab.szDisk)+1
    )) {
      p_fci_internal->fGetNextCabInVain=FALSE;
      p_fci_internal->fNextCab=TRUE;
      return fci_flush_cabinet( p_fci_internal, FALSE, pfnfcignc, pfnfcis);
    }

    /* if the FolderThreshold has been reached flush the folder automatically */
    if (p_fci_internal->cCompressedBytesInFolder >= p_fci_internal->ccab.cbFolderThresh)
        return fci_flush_folder(p_fci_internal, FALSE, pfnfcignc, pfnfcis);

    if( p_fci_internal->files_size>0 ) {
      if( !fci_flush_folder(p_fci_internal, FALSE, pfnfcignc, pfnfcis) ) return FALSE;
      p_fci_internal->fNewPrevious=TRUE;
    }
  } else {
    p_fci_internal->fNewPrevious=FALSE;
    if( p_fci_internal->files_size>0 || p_fci_internal->pending_data_size) {
      /* THIS MAY NEVER HAPPEN */
      /* set error structures */
      set_error( p_fci_internal, FCIERR_NONE, ERROR_GEN_FAILURE );
      return FALSE;
    }
  }

  return TRUE;
}