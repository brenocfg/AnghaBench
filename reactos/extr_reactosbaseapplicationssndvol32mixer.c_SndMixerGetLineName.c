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
typedef  int UINT ;
struct TYPE_7__ {scalar_t__ dwLineID; int /*<<< orphan*/  szShortName; int /*<<< orphan*/  szName; } ;
struct TYPE_6__ {TYPE_1__* Lines; scalar_t__ hmx; } ;
struct TYPE_5__ {TYPE_3__ Info; struct TYPE_5__* Next; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_1__* PSND_MIXER_DESTINATION ;
typedef  TYPE_2__* PSND_MIXER ;
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  TYPE_3__* LPMIXERLINE ;
typedef  int INT ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  _T (char) ; 
 scalar_t__ lstrlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

INT
SndMixerGetLineName(PSND_MIXER Mixer,
                    DWORD LineID,
                    LPTSTR lpBuffer,
                    UINT uSize,
                    BOOL LongName)
{
    if (Mixer->hmx)
    {
        UINT lnsz;
        PSND_MIXER_DESTINATION Line;
        LPMIXERLINE lpl = NULL;

        for (Line = Mixer->Lines; Line != NULL; Line = Line->Next)
        {
            if (Line->Info.dwLineID == LineID)
            {
                lpl = &Line->Info;
                break;
            }
        }

        if (lpl != NULL)
        {
            lnsz = (UINT) lstrlen(LongName ? lpl->szName : lpl->szShortName);
            if(lnsz + 1 > uSize)
            {
                return lnsz + 1;
            }
            else
            {
                memcpy(lpBuffer, LongName ? lpl->szName : lpl->szShortName, lnsz * sizeof(TCHAR));
                lpBuffer[lnsz] = _T('\0');
                return lnsz;
            }
        }
    }

    return -1;
}