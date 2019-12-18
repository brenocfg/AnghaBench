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
typedef  int /*<<< orphan*/  LPDIRECTSOUNDNOTIFY ;
typedef  int /*<<< orphan*/  IDirectSoundNotifyImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DS_OK ; 
 scalar_t__ IDirectSoundNotifyImpl_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT IDirectSoundNotifyImpl_Destroy(
    IDirectSoundNotifyImpl *pdsn)
{
    TRACE("(%p)\n",pdsn);

    while (IDirectSoundNotifyImpl_Release((LPDIRECTSOUNDNOTIFY)pdsn) > 0);

    return DS_OK;
}