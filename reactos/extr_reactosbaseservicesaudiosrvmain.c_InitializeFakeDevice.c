#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  PnP_AudioDevice ;

/* Variables and functions */
 int /*<<< orphan*/  AppendAudioDeviceToList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateDeviceDescriptor (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestroyDeviceDescriptor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 

VOID
InitializeFakeDevice()
{
    PnP_AudioDevice* list_node;

    list_node = CreateDeviceDescriptor(L"ThisDeviceDoesNotReallyExist", TRUE);
    AppendAudioDeviceToList(list_node);
    DestroyDeviceDescriptor(list_node);
}