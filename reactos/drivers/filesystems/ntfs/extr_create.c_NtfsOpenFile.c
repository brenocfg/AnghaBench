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
struct TYPE_4__ {scalar_t__ RelatedFileObject; } ;
typedef  int /*<<< orphan*/ * PWSTR ;
typedef  int /*<<< orphan*/ * PNTFS_FCB ;
typedef  TYPE_1__* PFILE_OBJECT ;
typedef  int /*<<< orphan*/  PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  ExFreePool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtfsAttachFCBToFileObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  NtfsGetFCBForFile (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NtfsGrabFCBFromTable (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NtfsMakeAbsoluteFilename (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  NtfsReleaseFCB (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAG_NTFS ; 

__attribute__((used)) static
NTSTATUS
NtfsOpenFile(PDEVICE_EXTENSION DeviceExt,
             PFILE_OBJECT FileObject,
             PWSTR FileName,
             BOOLEAN CaseSensitive,
             PNTFS_FCB * FoundFCB)
{
    PNTFS_FCB ParentFcb;
    PNTFS_FCB Fcb;
    NTSTATUS Status;
    PWSTR AbsFileName = NULL;

    DPRINT("NtfsOpenFile(%p, %p, %S, %s, %p)\n",
            DeviceExt,
            FileObject,
            FileName,
            CaseSensitive ? "TRUE" : "FALSE",
            FoundFCB);

    *FoundFCB = NULL;

    if (FileObject->RelatedFileObject)
    {
        DPRINT("Converting relative filename to absolute filename\n");

        Status = NtfsMakeAbsoluteFilename(FileObject->RelatedFileObject,
                                          FileName,
                                          &AbsFileName);
        if (AbsFileName) FileName = AbsFileName;
        if (!NT_SUCCESS(Status))
        {
            return Status;
        }
    }

    //FIXME: Get canonical path name (remove .'s, ..'s and extra separators)

    DPRINT("PathName to open: %S\n", FileName);

    /*  try first to find an existing FCB in memory  */
    DPRINT("Checking for existing FCB in memory\n");
    Fcb = NtfsGrabFCBFromTable(DeviceExt,
                               FileName);
    if (Fcb == NULL)
    {
        DPRINT("No existing FCB found, making a new one if file exists.\n");
        Status = NtfsGetFCBForFile(DeviceExt,
                                   &ParentFcb,
                                   &Fcb,
                                   FileName,
                                   CaseSensitive);
        if (ParentFcb != NULL)
        {
            NtfsReleaseFCB(DeviceExt,
                           ParentFcb);
        }

        if (!NT_SUCCESS(Status))
        {
            DPRINT("Could not make a new FCB, status: %x\n", Status);

            if (AbsFileName)
                ExFreePoolWithTag(AbsFileName, TAG_NTFS);

            return Status;
        }
    }

    DPRINT("Attaching FCB to fileObject\n");
    Status = NtfsAttachFCBToFileObject(DeviceExt,
                                       Fcb,
                                       FileObject);

    if (AbsFileName)
        ExFreePool(AbsFileName);

    *FoundFCB = Fcb;

    return Status;
}