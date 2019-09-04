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
typedef  int /*<<< orphan*/  WSADATA ;

/* Variables and functions */
 scalar_t__ DisplayOutput () ; 
 int Interval ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 scalar_t__ ParseCmdline (int,char**) ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 scalar_t__ WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bLoopOutput ; 

int main(int argc, char *argv[])
{
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        _tprintf(_T("WSAStartup() failed : %d\n"), WSAGetLastError());
        return -1;
    }

    if (ParseCmdline(argc, argv))
        return -1;

    if (bLoopOutput)
    {
        while (1)
        {
            if (DisplayOutput())
                return -1;
            Sleep(Interval*1000);
        }
    }

    if (DisplayOutput())
        return -1;
    else
        return 0;
}