#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int cab_UBYTE ;
typedef  int USHORT ;
struct TYPE_13__ {scalar_t__ (* read ) (int /*<<< orphan*/ ,int*,scalar_t__) ;int (* seek ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* free ) (char*) ;} ;
struct TYPE_12__ {int cbCabinet; int cFolders; int cFiles; int setID; int iCabinet; int fReserve; int hasprev; int hasnext; } ;
struct TYPE_11__ {int header_resv; int folder_resv; int block_resv; char* prevname; char* previnfo; char* nextname; char* nextinfo; int /*<<< orphan*/  hasnext; } ;
typedef  TYPE_1__* PMORE_ISCAB_INFO ;
typedef  TYPE_2__* PFDICABINETINFO ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  INT_PTR ;
typedef  TYPE_3__ FDI_Int ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int EndGetI16 (int*) ; 
 int EndGetI32 (int*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FDIERROR_CORRUPT_CABINET ; 
 int /*<<< orphan*/  FDIERROR_NOT_A_CABINET ; 
 int /*<<< orphan*/  FDIERROR_UNKNOWN_CABINET_VERSION ; 
 char* FDI_read_string (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int cfheadNEXT_CABINET ; 
 int cfheadPREV_CABINET ; 
 int cfheadRESERVE_PRESENT ; 
 int cfhead_CabinetIndex ; 
 int cfhead_CabinetSize ; 
 int cfhead_Flags ; 
 size_t cfhead_MajorVersion ; 
 size_t cfhead_MinorVersion ; 
 int cfhead_NumFiles ; 
 int cfhead_NumFolders ; 
 scalar_t__ cfhead_SIZEOF ; 
 int cfhead_SetID ; 
 int cfhead_Signature ; 
 size_t cfheadext_DataReserved ; 
 size_t cfheadext_FolderReserved ; 
 int cfheadext_HeaderReserved ; 
 scalar_t__ cfheadext_SIZEOF ; 
 int /*<<< orphan*/  set_error (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int*,scalar_t__) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int*,scalar_t__) ; 
 int stub3 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (char*) ; 
 int /*<<< orphan*/  stub5 (char*) ; 
 int /*<<< orphan*/  stub6 (char*) ; 
 int /*<<< orphan*/  stub7 (char*) ; 
 int /*<<< orphan*/  stub8 (char*) ; 
 int /*<<< orphan*/  stub9 (char*) ; 

__attribute__((used)) static BOOL FDI_read_entries(
        FDI_Int         *fdi,
        INT_PTR          hf,
        PFDICABINETINFO  pfdici,
        PMORE_ISCAB_INFO pmii)
{
  int num_folders, num_files, header_resv, folder_resv = 0;
  LONG cabsize;
  USHORT setid, cabidx, flags;
  cab_UBYTE buf[64], block_resv;
  char *prevname = NULL, *previnfo = NULL, *nextname = NULL, *nextinfo = NULL;

  TRACE("(fdi == ^%p, hf == %ld, pfdici == ^%p)\n", fdi, hf, pfdici);

  /* read in the CFHEADER */
  if (fdi->read(hf, buf, cfhead_SIZEOF) != cfhead_SIZEOF) {
    if (pmii) set_error( fdi, FDIERROR_NOT_A_CABINET, 0 );
    return FALSE;
  }

  /* check basic MSCF signature */
  if (EndGetI32(buf+cfhead_Signature) != 0x4643534d) {
    if (pmii) set_error( fdi, FDIERROR_NOT_A_CABINET, 0 );
    return FALSE;
  }

  /* get the cabinet size */
  cabsize = EndGetI32(buf+cfhead_CabinetSize);

  /* get the number of folders */
  num_folders = EndGetI16(buf+cfhead_NumFolders);

  /* get the number of files */
  num_files = EndGetI16(buf+cfhead_NumFiles);

  /* setid */
  setid = EndGetI16(buf+cfhead_SetID);

  /* cabinet (set) index */
  cabidx = EndGetI16(buf+cfhead_CabinetIndex);

  /* check the header revision */
  if ((buf[cfhead_MajorVersion] > 1) ||
      (buf[cfhead_MajorVersion] == 1 && buf[cfhead_MinorVersion] > 3))
  {
    WARN("cabinet format version > 1.3\n");
    if (pmii) set_error( fdi, FDIERROR_UNKNOWN_CABINET_VERSION, 0 /* ? */ );
    return FALSE;
  }

  /* pull the flags out */
  flags = EndGetI16(buf+cfhead_Flags);

  /* read the reserved-sizes part of header, if present */
  if (flags & cfheadRESERVE_PRESENT) {
    if (fdi->read(hf, buf, cfheadext_SIZEOF) != cfheadext_SIZEOF) {
      ERR("bunk reserve-sizes?\n");
      if (pmii) set_error( fdi, FDIERROR_CORRUPT_CABINET, 0 /* ? */ );
      return FALSE;
    }

    header_resv = EndGetI16(buf+cfheadext_HeaderReserved);
    if (pmii) pmii->header_resv = header_resv;
    folder_resv = buf[cfheadext_FolderReserved];
    if (pmii) pmii->folder_resv = folder_resv;
    block_resv  = buf[cfheadext_DataReserved];
    if (pmii) pmii->block_resv = block_resv;

    if (header_resv > 60000) {
      WARN("WARNING; header reserved space > 60000\n");
    }

    /* skip the reserved header */
    if ((header_resv) && (fdi->seek(hf, header_resv, SEEK_CUR) == -1)) {
      ERR("seek failure: header_resv\n");
      if (pmii) set_error( fdi, FDIERROR_CORRUPT_CABINET, 0 /* ? */ );
      return FALSE;
    }
  }

  if (flags & cfheadPREV_CABINET) {
    prevname = FDI_read_string(fdi, hf, cabsize);
    if (!prevname) {
      if (pmii) set_error( fdi, FDIERROR_CORRUPT_CABINET, 0 /* ? */ );
      return FALSE;
    } else
      if (pmii)
        pmii->prevname = prevname;
      else
        fdi->free(prevname);
    previnfo = FDI_read_string(fdi, hf, cabsize);
    if (previnfo) {
      if (pmii) 
        pmii->previnfo = previnfo;
      else
        fdi->free(previnfo);
    }
  }

  if (flags & cfheadNEXT_CABINET) {
    if (pmii)
      pmii->hasnext = TRUE;
    nextname = FDI_read_string(fdi, hf, cabsize);
    if (!nextname) {
      if ((flags & cfheadPREV_CABINET) && pmii) {
        if (pmii->prevname) fdi->free(prevname);
        if (pmii->previnfo) fdi->free(previnfo);
      }
      set_error( fdi, FDIERROR_CORRUPT_CABINET, 0 /* ? */ );
      return FALSE;
    } else
      if (pmii)
        pmii->nextname = nextname;
      else
        fdi->free(nextname);
    nextinfo = FDI_read_string(fdi, hf, cabsize);
    if (nextinfo) {
      if (pmii)
        pmii->nextinfo = nextinfo;
      else
        fdi->free(nextinfo);
    }
  }

  /* we could process the whole cabinet searching for problems;
     instead lets stop here.  Now let's fill out the paperwork */
  pfdici->cbCabinet = cabsize;
  pfdici->cFolders  = num_folders;
  pfdici->cFiles    = num_files;
  pfdici->setID     = setid;
  pfdici->iCabinet  = cabidx;
  pfdici->fReserve  = (flags & cfheadRESERVE_PRESENT) != 0;
  pfdici->hasprev   = (flags & cfheadPREV_CABINET) != 0;
  pfdici->hasnext   = (flags & cfheadNEXT_CABINET) != 0;
  return TRUE;
}