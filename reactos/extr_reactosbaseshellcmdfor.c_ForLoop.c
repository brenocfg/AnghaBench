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
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  PARSED_COMMAND ;
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  Exiting (int /*<<< orphan*/ *) ; 
 scalar_t__ GetNextElement (int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int RunInstance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _itot (int,int /*<<< orphan*/ *,int) ; 
 int _tcstol (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static INT ForLoop(PARSED_COMMAND *Cmd, LPTSTR List, TCHAR *Buffer)
{
    enum { START, STEP, END };
    INT params[3] = { 0, 0, 0 };
    INT i;
    INT Ret = 0;

    TCHAR *Start, *End = List;
    for (i = 0; i < 3 && GetNextElement(&Start, &End); i++)
        params[i] = _tcstol(Start, NULL, 0);

    i = params[START];
    while (!Exiting(Cmd) &&
           (params[STEP] >= 0 ? (i <= params[END]) : (i >= params[END])))
    {
        _itot(i, Buffer, 10);
        Ret = RunInstance(Cmd);
        i += params[STEP];
    }
    return Ret;
}