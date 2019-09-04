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
struct TYPE_3__ {int (* Handler ) (int,int /*<<< orphan*/  const**) ;int /*<<< orphan*/  Command; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_1__ HandlerItem ;

/* Variables and functions */
 scalar_t__ _tcsicmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int stub1 (int,int /*<<< orphan*/  const**) ; 

int FindHandler(int argc,
                const TCHAR *argv[],
                HandlerItem * HandlersList,
                int HandlerListCount,
                void (*UsageHelper)(const TCHAR *))
{
    int i;
    int ret;
    const TCHAR * Command;

    ret = 1;
    Command = NULL;
    i = HandlerListCount;

    /* If we have a command, does it match a known one? */
    if (argc > 1)
    {
        /* Browse all the known commands finding the right one */
        Command = argv[1];
        for (i = 0; i < HandlerListCount; ++i)
        {
            if (_tcsicmp(Command, HandlersList[i].Command) == 0)
            {
                ret = HandlersList[i].Handler(argc - 1, &argv[1]);
                break;
            }
        }
    }

    /* We failed finding someone to handle the caller's needs, print out */
    if (i == HandlerListCount)
    {
        UsageHelper(Command);
    }

    return ret;
}