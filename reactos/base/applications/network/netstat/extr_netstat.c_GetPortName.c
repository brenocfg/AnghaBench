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
struct servent {int /*<<< orphan*/  s_name; } ;
typedef  int /*<<< orphan*/  WORD ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  PCSTR ;
typedef  int /*<<< orphan*/ * PCHAR ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 scalar_t__ bDoShowNumbers ; 
 struct servent* getservbyport (scalar_t__,int /*<<< orphan*/ ) ; 
 int htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

PCHAR
GetPortName(UINT Port, PCSTR Proto, CHAR Name[], INT NameLen)
{
    struct servent *pServent;

    if (bDoShowNumbers)
    {
        sprintf(Name, "%d", htons((WORD)Port));
        return Name;
    }
    /* Try to translate to a name */
    if ((pServent = getservbyport(Port, Proto)))
        strcpy(Name, pServent->s_name );
    else
        sprintf(Name, "%d", htons((WORD)Port));
    return Name;
}