#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int set_class; } ;
typedef  TYPE_2__ setattr_upcall_args ;
struct TYPE_10__ {TYPE_2__ setattr; } ;
struct TYPE_12__ {TYPE_1__ args; } ;
typedef  TYPE_3__ nfs41_upcall ;

/* Variables and functions */
 int ERROR_NOT_SUPPORTED ; 
#define  FileAllocationInformation 133 
#define  FileBasicInformation 132 
#define  FileDispositionInformation 131 
#define  FileEndOfFileInformation 130 
#define  FileLinkInformation 129 
#define  FileRenameInformation 128 
 int /*<<< orphan*/  eprintf (char*,int) ; 
 int handle_nfs41_link (TYPE_2__*) ; 
 int handle_nfs41_remove (TYPE_2__*) ; 
 int handle_nfs41_rename (TYPE_2__*) ; 
 int handle_nfs41_set_size (TYPE_2__*) ; 
 int handle_nfs41_setattr (TYPE_2__*) ; 

__attribute__((used)) static int handle_setattr(nfs41_upcall *upcall)
{
    setattr_upcall_args *args = &upcall->args.setattr;
    int status;

    switch (args->set_class) {
    case FileBasicInformation:
        status = handle_nfs41_setattr(args);
        break;
    case FileDispositionInformation:
        status = handle_nfs41_remove(args);
        break;
    case FileRenameInformation:
        status = handle_nfs41_rename(args);
        break;
    case FileAllocationInformation:
    case FileEndOfFileInformation:
        status = handle_nfs41_set_size(args);
        break;
    case FileLinkInformation:
        status = handle_nfs41_link(args);
        break;
    default:
        eprintf("unknown set_file information class %d\n",
            args->set_class);
        status = ERROR_NOT_SUPPORTED;
        break;
    }

    return status;
}