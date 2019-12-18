#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* ULONG ;
struct TYPE_7__ {void* tei_instance; void* tei_entity; } ;
struct TYPE_6__ {void* toi_id; void* toi_type; void* toi_class; TYPE_2__ toi_entity; } ;
struct TYPE_8__ {TYPE_1__ ID; } ;
typedef  TYPE_3__ TCP_REQUEST_QUERY_INFORMATION_EX ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/ * PULONG ;
typedef  int /*<<< orphan*/  PFILE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  IOCTL_TCP_QUERY_INFORMATION_EX ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_3__*,int) ; 
 int /*<<< orphan*/  TdiQueryDeviceControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

NTSTATUS TdiQueryInformationEx(
    PFILE_OBJECT FileObject,
    ULONG Entity,
    ULONG Instance,
    ULONG Class,
    ULONG Type,
    ULONG Id,
    PVOID OutputBuffer,
    PULONG OutputLength)
/*
 * FUNCTION: Extended query for information
 * ARGUMENTS:
 *     FileObject   = Pointer to file object
 *     Entity       = Entity
 *     Instance     = Instance
 *     Class        = Entity class
 *     Type         = Entity type
 *     Id           = Entity id
 *     OutputBuffer = Address of buffer to place data
 *     OutputLength = Address of buffer with length of OutputBuffer (updated)
 * RETURNS:
 *     Status of operation
 */
{
    TCP_REQUEST_QUERY_INFORMATION_EX QueryInfo;

    RtlZeroMemory(&QueryInfo, sizeof(TCP_REQUEST_QUERY_INFORMATION_EX));
    QueryInfo.ID.toi_entity.tei_entity   = Entity;
    QueryInfo.ID.toi_entity.tei_instance = Instance;
    QueryInfo.ID.toi_class = Class;
    QueryInfo.ID.toi_type  = Type;
    QueryInfo.ID.toi_id    = Id;

    return TdiQueryDeviceControl(FileObject,                                /* Transport/connection object */
                                 IOCTL_TCP_QUERY_INFORMATION_EX,            /* Control code */
                                 &QueryInfo,                                /* Input buffer */
                                 sizeof(TCP_REQUEST_QUERY_INFORMATION_EX),  /* Input buffer length */
                                 OutputBuffer,                              /* Output buffer */
                                 *OutputLength,                             /* Output buffer length */
                                 OutputLength);                             /* Return information */
}