#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_7__ {int query_class; int basic_info; int std_info; int tag_info; int intr_info; int network_info; int ctime; } ;
struct TYPE_5__ {TYPE_3__ getattr; } ;
struct TYPE_6__ {TYPE_1__ args; } ;
typedef  TYPE_2__ nfs41_upcall ;
typedef  int /*<<< orphan*/  info_len ;
typedef  TYPE_3__ getattr_upcall_args ;

/* Variables and functions */
#define  FileAttributeTagInformation 132 
#define  FileBasicInformation 131 
#define  FileInternalInformation 130 
#define  FileNetworkOpenInformation 129 
#define  FileStandardInformation 128 
 int /*<<< orphan*/  dprintf (int,char*,int) ; 
 int /*<<< orphan*/  eprintf (char*,int) ; 
 int safe_write (unsigned char**,int*,int*,int) ; 

__attribute__((used)) static int marshall_getattr(unsigned char *buffer, uint32_t *length, nfs41_upcall *upcall)
{
    int status;
    getattr_upcall_args *args = &upcall->args.getattr;
    uint32_t info_len;

    switch (args->query_class) {
    case FileBasicInformation:
        info_len = sizeof(args->basic_info);
        status = safe_write(&buffer, length, &info_len, sizeof(info_len));
        if (status) goto out;
        status = safe_write(&buffer, length, &args->basic_info, info_len);
        if (status) goto out;
        break;
    case FileStandardInformation:
        info_len = sizeof(args->std_info);
        status = safe_write(&buffer, length, &info_len, sizeof(info_len));
        if (status) goto out;
        status = safe_write(&buffer, length, &args->std_info, info_len);
        if (status) goto out;
        break;
    case FileAttributeTagInformation:
        info_len = sizeof(args->tag_info);
        status = safe_write(&buffer, length, &info_len, sizeof(info_len));
        if (status) goto out;
        status = safe_write(&buffer, length, &args->tag_info, info_len);
        if (status) goto out;
        break;
    case FileInternalInformation:
        info_len = sizeof(args->intr_info);
        status = safe_write(&buffer, length, &info_len, sizeof(info_len));
        if (status) goto out;
        status = safe_write(&buffer, length, &args->intr_info, info_len);
        if (status) goto out;
        break;
    case FileNetworkOpenInformation:
        info_len = sizeof(args->network_info);
        status = safe_write(&buffer, length, &info_len, sizeof(info_len));
        if (status) goto out;
        status = safe_write(&buffer, length, &args->network_info, info_len);
        if (status) goto out;
        break;
    default:
        eprintf("unknown file query class %d\n", args->query_class);
        status = 103;
        goto out;
    }
    status = safe_write(&buffer, length, &args->ctime, sizeof(args->ctime));
    if (status) goto out;
    dprintf(1, "NFS41_FILE_QUERY: downcall changattr=%llu\n", args->ctime);
out:
    return status;
}