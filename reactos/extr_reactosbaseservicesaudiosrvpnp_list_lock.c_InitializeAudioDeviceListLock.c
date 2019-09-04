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
struct TYPE_3__ {int nLength; int /*<<< orphan*/  bInheritHandle; int /*<<< orphan*/ * lpSecurityDescriptor; } ;
typedef  int /*<<< orphan*/  SECURITY_DESCRIPTOR ;
typedef  TYPE_1__ SECURITY_ATTRIBUTES ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_LIST_LOCK_NAME ; 
 int /*<<< orphan*/ * CreateMutex (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InitializeSecurityDescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SECURITY_DESCRIPTOR_REVISION ; 
 int /*<<< orphan*/  SetSecurityDescriptorDacl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * audio_device_list_lock ; 

BOOL
InitializeAudioDeviceListLock()
{
    /* The security stuff is to make sure the mutex can be grabbed by
       other processes - is this the best idea though ??? */

    SECURITY_DESCRIPTOR security_descriptor;
    SECURITY_ATTRIBUTES security;

    InitializeSecurityDescriptor(&security_descriptor, SECURITY_DESCRIPTOR_REVISION);
    SetSecurityDescriptorDacl(&security_descriptor, TRUE, 0, FALSE);

    security.nLength = sizeof(SECURITY_ATTRIBUTES);
    security.lpSecurityDescriptor = &security_descriptor;
    security.bInheritHandle = FALSE;

    audio_device_list_lock = CreateMutex(&security,
                                         FALSE,
                                         AUDIO_LIST_LOCK_NAME);

    return ( audio_device_list_lock != NULL );
}