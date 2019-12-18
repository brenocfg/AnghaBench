#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* self; } ;
typedef  TYPE_1__ MIDIMAPDATA ;
typedef  int /*<<< orphan*/  LPMIDIOPENDESC ;
typedef  scalar_t__ DWORD_PTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  MIDIERR_INVALIDSETUP ; 
 scalar_t__ MIDIMAP_LoadSettings (TYPE_1__*) ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  MMSYSERR_NOMEM ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static	DWORD	modOpen(DWORD_PTR *lpdwUser, LPMIDIOPENDESC lpDesc, DWORD dwFlags)
{
    MIDIMAPDATA*	mom = HeapAlloc(GetProcessHeap(), 0, sizeof(MIDIMAPDATA));

    TRACE("(%p %p %08lx)\n", lpdwUser, lpDesc, dwFlags);

    if (!mom) return MMSYSERR_NOMEM;

    if (MIDIMAP_LoadSettings(mom))
    {
	*lpdwUser = (DWORD_PTR)mom;
	mom->self = mom;

	return MMSYSERR_NOERROR;
    }
    HeapFree(GetProcessHeap(), 0, mom);
    return MIDIERR_INVALIDSETUP;
}