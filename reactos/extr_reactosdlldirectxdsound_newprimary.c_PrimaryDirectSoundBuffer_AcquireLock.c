#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_2__ {int /*<<< orphan*/  Lock; } ;
typedef  int /*<<< orphan*/  LPDIRECTSOUNDBUFFER8 ;
typedef  TYPE_1__* LPCDirectSoundBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  CDirectSoundBuffer ; 
 int /*<<< orphan*/  CONTAINING_RECORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpVtbl ; 

VOID
PrimaryDirectSoundBuffer_AcquireLock(
    LPDIRECTSOUNDBUFFER8 iface)
{
    LPCDirectSoundBuffer This = (LPCDirectSoundBuffer)CONTAINING_RECORD(iface, CDirectSoundBuffer, lpVtbl);

    EnterCriticalSection(&This->Lock);


}