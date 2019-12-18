#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int cab_UWORD ;
typedef  int cab_ULONG ;
typedef  scalar_t__ cab_UBYTE ;
struct TYPE_19__ {int versionMinor; int versionMajor; struct TYPE_19__* signature; void* iCabinet; void* setID; void* flags; void* cFiles; void* cFolders; void* coffFiles; void* cbCabinet; } ;
struct TYPE_17__ {int cbReserveCFHeader; int setID; int iCab; int /*<<< orphan*/  szCab; int /*<<< orphan*/  szCabPath; scalar_t__ cbReserveCFData; scalar_t__ cbReserveCFFolder; } ;
struct TYPE_18__ {int folders_size; int placed_files_size; int folders_data_size; int cFolders; int cFiles; int (* open ) (char*,int,int,int*,int /*<<< orphan*/ ) ;int (* write ) (int,TYPE_4__*,int,int*,int /*<<< orphan*/ ) ;scalar_t__ (* seek ) (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  pv; int /*<<< orphan*/  (* delete ) (char*,int*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* close ) (int,int*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  estimatedCabinetSize; TYPE_2__ ccab; TYPE_1__* pccab; int /*<<< orphan*/  szPrevDisk; int /*<<< orphan*/  szPrevCab; scalar_t__ fNextCab; scalar_t__ fPrevCab; scalar_t__ data_out; } ;
struct TYPE_16__ {int /*<<< orphan*/  szDisk; int /*<<< orphan*/  szCab; } ;
typedef  int /*<<< orphan*/  (* PFNFCISTATUS ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;
typedef  int INT_PTR ;
typedef  TYPE_3__ FCI_Int ;
typedef  TYPE_4__ CFHEADER ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int CB_MAX_CABINET_NAME ; 
 int CB_MAX_CAB_PATH ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FCIERR_CAB_FILE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TRUE ; 
 int _O_BINARY ; 
 int _O_CREAT ; 
 int _O_RDWR ; 
 int _O_TRUNC ; 
 int _S_IREAD ; 
 int _S_IWRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 int cfheadNEXT_CABINET ; 
 int cfheadPREV_CABINET ; 
 int cfheadRESERVE_PRESENT ; 
 void* fci_endian_ulong (int) ; 
 void* fci_endian_uword (int) ; 
 int get_header_size (TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reset_cabinet (TYPE_3__*) ; 
 int /*<<< orphan*/  set_error (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  statusCabinet ; 
 int /*<<< orphan*/  strcat (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 
 int stub1 (char*,int,int,int*,int /*<<< orphan*/ ) ; 
 int stub2 (int,TYPE_4__*,int,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int stub4 (int,TYPE_4__*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (char*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_data_blocks (TYPE_3__*,int,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  write_files (TYPE_3__*,int,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  write_folders (TYPE_3__*,int,int,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ )) ; 

__attribute__((used)) static BOOL write_cabinet( FCI_Int *fci, PFNFCISTATUS status_callback )
{
    char filename[CB_MAX_CAB_PATH + CB_MAX_CABINET_NAME];
    int err;
    char *ptr;
    INT_PTR handle;
    CFHEADER *cfheader = (CFHEADER *)fci->data_out;
    cab_UWORD flags = 0;
    cab_ULONG header_size = get_header_size( fci );
    cab_ULONG total_size = header_size + fci->folders_size +
                           fci->placed_files_size + fci->folders_data_size;

    assert( header_size <= sizeof(fci->data_out) );
    memset( cfheader, 0, header_size );

    if (fci->fPrevCab) flags |= cfheadPREV_CABINET;
    if (fci->fNextCab) flags |= cfheadNEXT_CABINET;
    if (fci->ccab.cbReserveCFHeader || fci->ccab.cbReserveCFFolder || fci->ccab.cbReserveCFData)
      flags |= cfheadRESERVE_PRESENT;

    memcpy( cfheader->signature, "!CAB", 4 );
    cfheader->cbCabinet    = fci_endian_ulong( total_size );
    cfheader->coffFiles    = fci_endian_ulong( header_size + fci->folders_size );
    cfheader->versionMinor = 3;
    cfheader->versionMajor = 1;
    cfheader->cFolders     = fci_endian_uword( fci->cFolders );
    cfheader->cFiles       = fci_endian_uword( fci->cFiles );
    cfheader->flags        = fci_endian_uword( flags );
    cfheader->setID        = fci_endian_uword( fci->ccab.setID );
    cfheader->iCabinet     = fci_endian_uword( fci->ccab.iCab );
    ptr = (char *)(cfheader + 1);

    if (flags & cfheadRESERVE_PRESENT)
    {
        struct
        {
            cab_UWORD cbCFHeader;
            cab_UBYTE cbCFFolder;
            cab_UBYTE cbCFData;
        } *reserve = (void *)ptr;

        reserve->cbCFHeader = fci_endian_uword( fci->ccab.cbReserveCFHeader );
        reserve->cbCFFolder = fci->ccab.cbReserveCFFolder;
        reserve->cbCFData   = fci->ccab.cbReserveCFData;
        ptr = (char *)(reserve + 1);
    }
    ptr += fci->ccab.cbReserveCFHeader;

    if (flags & cfheadPREV_CABINET)
    {
        strcpy( ptr, fci->szPrevCab );
        ptr += strlen( ptr ) + 1;
        strcpy( ptr, fci->szPrevDisk );
        ptr += strlen( ptr ) + 1;
    }

    if (flags & cfheadNEXT_CABINET)
    {
        strcpy( ptr, fci->pccab->szCab );
        ptr += strlen( ptr ) + 1;
        strcpy( ptr, fci->pccab->szDisk );
        ptr += strlen( ptr ) + 1;
    }

    assert( ptr - (char *)cfheader == header_size );

    strcpy( filename, fci->ccab.szCabPath );
    strcat( filename, fci->ccab.szCab );

    if ((handle = fci->open( filename, _O_RDWR | _O_CREAT | _O_TRUNC | _O_BINARY,
                             _S_IREAD | _S_IWRITE, &err, fci->pv )) == -1)
    {
        set_error( fci, FCIERR_CAB_FILE, err );
        return FALSE;
    }

    if (fci->write( handle, cfheader, header_size, &err, fci->pv ) != header_size)
    {
        set_error( fci, FCIERR_CAB_FILE, err );
        goto failed;
    }

    /* add size of header size of all CFFOLDERs and size of all CFFILEs */
    header_size += fci->placed_files_size + fci->folders_size;
    if (!write_folders( fci, handle, header_size, status_callback )) goto failed;
    if (!write_files( fci, handle, status_callback )) goto failed;
    if (!write_data_blocks( fci, handle, status_callback )) goto failed;

    /* update the signature */
    if (fci->seek( handle, 0, SEEK_SET, &err, fci->pv ) != 0 )
    {
        set_error( fci, FCIERR_CAB_FILE, err );
        goto failed;
    }
    memcpy( cfheader->signature, "MSCF", 4 );
    if (fci->write( handle, cfheader->signature, 4, &err, fci->pv ) != 4)
    {
        set_error( fci, FCIERR_CAB_FILE, err );
        goto failed;
    }
    fci->close( handle, &err, fci->pv );

    reset_cabinet( fci );
    status_callback( statusCabinet, fci->estimatedCabinetSize, total_size, fci->pv );
    return TRUE;

failed:
    fci->close( handle, &err, fci->pv );
    fci->delete( filename, &err, fci->pv );
    return FALSE;
}