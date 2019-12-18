#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_7__ {int /*<<< orphan*/  Id; int /*<<< orphan*/  Flags; int /*<<< orphan*/  Set; } ;
struct TYPE_10__ {TYPE_1__ Property; int /*<<< orphan*/  PinId; } ;
struct TYPE_9__ {int /*<<< orphan*/  FileObject; } ;
struct TYPE_8__ {int /*<<< orphan*/  PinId; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_2__* PKSPIN_CONNECT ;
typedef  scalar_t__ PKSPIN_CINSTANCES ;
typedef  TYPE_3__* PKSAUDIO_DEVICE_ENTRY ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_4__ KSP_PIN ;
typedef  int /*<<< orphan*/  KSPIN_CINSTANCES ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOCTL_KS_PROPERTY ; 
 int /*<<< orphan*/  KSPROPERTY_PIN_CINSTANCES ; 
 int /*<<< orphan*/  KSPROPERTY_TYPE_GET ; 
 int /*<<< orphan*/  KSPROPSETID_Pin ; 
 int /*<<< orphan*/  KernelMode ; 
 int /*<<< orphan*/  KsSynchronousIoControlDevice (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

NTSTATUS
GetPinInstanceCount(
    PKSAUDIO_DEVICE_ENTRY Entry,
    PKSPIN_CINSTANCES PinInstances,
    PKSPIN_CONNECT PinConnect)
{
    KSP_PIN PinRequest;
    ULONG BytesReturned;

    /* query the instance count */
    PinRequest.PinId = PinConnect->PinId;
    PinRequest.Property.Set = KSPROPSETID_Pin;
    PinRequest.Property.Flags = KSPROPERTY_TYPE_GET;
    PinRequest.Property.Id = KSPROPERTY_PIN_CINSTANCES;
	ASSERT(Entry->FileObject);
    return KsSynchronousIoControlDevice(Entry->FileObject, KernelMode, IOCTL_KS_PROPERTY, (PVOID)&PinRequest, sizeof(KSP_PIN), (PVOID)PinInstances, sizeof(KSPIN_CINSTANCES), &BytesReturned);

}