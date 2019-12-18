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
typedef  size_t ULONG ;
struct TYPE_3__ {scalar_t__ Number; char* String; } ;
typedef  TYPE_1__ MUI_STRING ;
typedef  char* LPSTR ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  FindLanguageIndex () ; 
 TYPE_1__* FindMUIStringEntries () ; 
 int /*<<< orphan*/  POPUP_WAIT_NONE ; 
 int /*<<< orphan*/  PopupError (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,size_t,int /*<<< orphan*/ ) ; 

LPSTR
MUIGetString(
    ULONG Number)
{
    ULONG i;
    const MUI_STRING * entry;
    CHAR szErr[128];

    entry = FindMUIStringEntries();
    if (entry)
    {
        for (i = 0; entry[i].Number != 0; i++)
        {
            if (entry[i].Number == Number)
            {
                return entry[i].String;
            }
        }
    }

    sprintf(szErr, "Error: failed find string id %lu for language index %lu\n", Number, FindLanguageIndex());

    PopupError(szErr,
               NULL,
               NULL,
               POPUP_WAIT_NONE);

    return "<nostring>";
}