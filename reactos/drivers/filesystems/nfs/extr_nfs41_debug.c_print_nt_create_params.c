#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int FileAttributes; scalar_t__ Disposition; int CreateOptions; int ShareAccess; int DesiredAccess; } ;
typedef  TYPE_1__ NT_CREATE_PARAMETERS ;

/* Variables and functions */
 int DELETE ; 
 int /*<<< orphan*/  DbgP (char*,...) ; 
 int FILE_APPEND_DATA ; 
 int FILE_ATTRIBUTE_ARCHIVE ; 
 int FILE_ATTRIBUTE_COMPRESSED ; 
 int FILE_ATTRIBUTE_DEVICE ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int FILE_ATTRIBUTE_ENCRYPTED ; 
 int FILE_ATTRIBUTE_HIDDEN ; 
 int FILE_ATTRIBUTE_NORMAL ; 
 int FILE_ATTRIBUTE_NOT_CONTENT_INDEXED ; 
 int FILE_ATTRIBUTE_READONLY ; 
 int FILE_ATTRIBUTE_REPARSE_POINT ; 
 int FILE_ATTRIBUTE_SPARSE_FILE ; 
 int FILE_ATTRIBUTE_SYSTEM ; 
 int FILE_ATTRIBUTE_TEMPORARY ; 
 int FILE_ATTRIBUTE_VIRTUAL ; 
 int FILE_COMPLETE_IF_OPLOCKED ; 
 scalar_t__ FILE_CREATE ; 
 int FILE_CREATE_TREE_CONNECTION ; 
 int FILE_DELETE_ON_CLOSE ; 
 int FILE_DIRECTORY_FILE ; 
 int FILE_EXECUTE ; 
 int FILE_LIST_DIRECTORY ; 
 int FILE_NON_DIRECTORY_FILE ; 
 int FILE_NO_EA_KNOWLEDGE ; 
 int FILE_NO_INTERMEDIATE_BUFFERING ; 
 scalar_t__ FILE_OPEN ; 
 int FILE_OPEN_BY_FILE_ID ; 
 int FILE_OPEN_FOR_BACKUP_INTENT ; 
 scalar_t__ FILE_OPEN_IF ; 
 int FILE_OPEN_REPARSE_POINT ; 
 scalar_t__ FILE_OVERWRITE ; 
 scalar_t__ FILE_OVERWRITE_IF ; 
 int FILE_RANDOM_ACCESS ; 
 int FILE_READ_ATTRIBUTES ; 
 int FILE_READ_DATA ; 
 int FILE_READ_EA ; 
 int FILE_RESERVE_OPFILTER ; 
 int FILE_SEQUENTIAL_ONLY ; 
 int FILE_SHARE_DELETE ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 scalar_t__ FILE_SUPERSEDE ; 
 int FILE_SYNCHRONOUS_IO_ALERT ; 
 int FILE_SYNCHRONOUS_IO_NONALERT ; 
 int FILE_TRAVERSE ; 
 int FILE_WRITE_ATTRIBUTES ; 
 int FILE_WRITE_DATA ; 
 int FILE_WRITE_EA ; 
 int FILE_WRITE_THROUGH ; 
 int READ_CONTROL ; 
 int STANDARD_RIGHTS_READ ; 
 int SYNCHRONIZE ; 
 int WRITE_DAC ; 
 int WRITE_OWNER ; 

void print_nt_create_params(int on, NT_CREATE_PARAMETERS params)
{
    if (!on) return;
    if (params.FileAttributes)
        DbgP("File attributes %x: %s %s %s %s %s %s %s %s %s %s %s %s %s %s\n", 
            params.FileAttributes,
            (params.FileAttributes & FILE_ATTRIBUTE_TEMPORARY)?"TEMPFILE ":"",
            (params.FileAttributes & FILE_ATTRIBUTE_READONLY)?"READONLY ":"",
            (params.FileAttributes & FILE_ATTRIBUTE_HIDDEN)?"HIDDEN ":"",
            (params.FileAttributes & FILE_ATTRIBUTE_SYSTEM)?"SYSTEM ":"",
            (params.FileAttributes & FILE_ATTRIBUTE_ARCHIVE)?"ARCHIVE ":"",
            (params.FileAttributes & FILE_ATTRIBUTE_DIRECTORY)?"DIR ":"",
            (params.FileAttributes & FILE_ATTRIBUTE_DEVICE)?"DEVICE ":"",
            (params.FileAttributes & FILE_ATTRIBUTE_NORMAL)?"NORMAL ":"",
            (params.FileAttributes & FILE_ATTRIBUTE_SPARSE_FILE)?"SPARSE_FILE ":"",
            (params.FileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)?"REPARSE_POINT ":"",
            (params.FileAttributes & FILE_ATTRIBUTE_COMPRESSED)?"COMPRESSED ":"",
            (params.FileAttributes & FILE_ATTRIBUTE_NOT_CONTENT_INDEXED)?"NOT INDEXED ":"",
            (params.FileAttributes & FILE_ATTRIBUTE_ENCRYPTED)?"ENCRYPTED ":"",
            (params.FileAttributes & FILE_ATTRIBUTE_VIRTUAL)?"VIRTUAL":"");
 
    if (params.Disposition  == FILE_SUPERSEDE)
        DbgP("Create Dispositions: FILE_SUPERSEDE\n");
    if (params.Disposition == FILE_CREATE)
        DbgP("Create Dispositions: FILE_CREATE\n");
    if (params.Disposition == FILE_OPEN)
        DbgP("Create Dispositions: FILE_OPEN\n");
    if (params.Disposition == FILE_OPEN_IF)
        DbgP("Create Dispositions: FILE_OPEN_IF\n");
    if (params.Disposition == FILE_OVERWRITE)
        DbgP("Create Dispositions: FILE_OVERWRITE\n");
    if (params.Disposition == FILE_OVERWRITE_IF)
        DbgP("Create Dispositions: FILE_OVERWRITE_IF\n");

    DbgP("Create Attributes: 0x%x %s %s %s %s %s %s %s %s %s %s %s %s %s %s "
        "%s %s\n", params.CreateOptions, 
        (params.CreateOptions & FILE_DIRECTORY_FILE)?"DIRFILE":"",
        (params.CreateOptions & FILE_NON_DIRECTORY_FILE)?"FILE":"",
        (params.CreateOptions & FILE_DELETE_ON_CLOSE)?"DELETE_ON_CLOSE":"",
        (params.CreateOptions & FILE_WRITE_THROUGH)?"WRITE_THROUGH":"",
        (params.CreateOptions & FILE_SEQUENTIAL_ONLY)?"SEQUENTIAL":"",
        (params.CreateOptions & FILE_RANDOM_ACCESS)?"RANDOM":"",
        (params.CreateOptions & FILE_NO_INTERMEDIATE_BUFFERING)?"NO_BUFFERING":"",
        (params.CreateOptions & FILE_SYNCHRONOUS_IO_ALERT)?"SYNC_ALERT":"",
        (params.CreateOptions & FILE_SYNCHRONOUS_IO_NONALERT)?"SYNC_NOALERT":"",
        (params.CreateOptions & FILE_CREATE_TREE_CONNECTION)?"CREATE_TREE_CONN":"",
        (params.CreateOptions & FILE_COMPLETE_IF_OPLOCKED)?"OPLOCKED":"",
        (params.CreateOptions & FILE_NO_EA_KNOWLEDGE)?"NO_EA":"",
        (params.CreateOptions & FILE_OPEN_REPARSE_POINT)?"OPEN_REPARSE":"",
        (params.CreateOptions & FILE_OPEN_BY_FILE_ID)?"BY_ID":"",
        (params.CreateOptions & FILE_OPEN_FOR_BACKUP_INTENT)?"4_BACKUP":"",
        (params.CreateOptions & FILE_RESERVE_OPFILTER)?"OPFILTER":"");

    DbgP("Share Access: %s %s %s\n", 
        (params.ShareAccess & FILE_SHARE_READ)?"READ":"",
        (params.ShareAccess & FILE_SHARE_WRITE)?"WRITE":"",
        (params.ShareAccess & FILE_SHARE_DELETE)?"DELETE":"");

    DbgP("Desired Access: 0x%x %s %s %s %s %s %s %s %s %s %s %s\n", 
        params.DesiredAccess,
        (params.DesiredAccess & FILE_READ_DATA)?"READ":"",
        (params.DesiredAccess & STANDARD_RIGHTS_READ)?"READ_ACL":"",
        (params.DesiredAccess & FILE_READ_ATTRIBUTES)?"GETATTR":"",
        (params.DesiredAccess & FILE_READ_EA)?"READ_EA":"",
        (params.DesiredAccess & FILE_WRITE_DATA)?"WRITE":"",
        (params.DesiredAccess & FILE_WRITE_ATTRIBUTES)?"SETATTR":"",
        (params.DesiredAccess & FILE_WRITE_EA)?"WRITE_EA":"",
        (params.DesiredAccess & FILE_APPEND_DATA)?"APPEND":"",
        (params.DesiredAccess & FILE_EXECUTE)?"EXEC":"",
        (params.DesiredAccess & FILE_LIST_DIRECTORY)?"LSDIR":"",
        (params.DesiredAccess & FILE_TRAVERSE)?"TRAVERSE":"",
        (params.DesiredAccess & FILE_LIST_DIRECTORY)?"LSDIR":"",
        (params.DesiredAccess & DELETE)?"DELETE":"",
        (params.DesiredAccess & READ_CONTROL)?"READ_CONTROL":"",
        (params.DesiredAccess & WRITE_DAC)?"WRITE_DAC":"",
        (params.DesiredAccess & WRITE_OWNER)?"WRITE_OWNER":"",
        (params.DesiredAccess & SYNCHRONIZE)?"SYNCHRONIZE":"");
}