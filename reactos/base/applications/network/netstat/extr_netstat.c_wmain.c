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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  WSADATA ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ConInitStdStreams () ; 
 int /*<<< orphan*/  ConResPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ DisplayOutput () ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  IDS_ERROR_WSA_START ; 
 int Interval ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int /*<<< orphan*/  ParseCmdline (int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  StdErr ; 
 int /*<<< orphan*/  WSACleanup () ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 scalar_t__ WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bLoopOutput ; 

int wmain(int argc, wchar_t *argv[])
{
    BOOL Success;
    WSADATA wsaData;

    /* Initialize the Console Standard Streams */
    ConInitStdStreams();

    if (!ParseCmdline(argc, argv))
        return EXIT_FAILURE;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        ConResPrintf(StdErr, IDS_ERROR_WSA_START, WSAGetLastError());
        return EXIT_FAILURE;
    }

    Success = DisplayOutput();
    while (bLoopOutput && Success)
    {
        Sleep(Interval*1000);
        Success = DisplayOutput();
    }

    WSACleanup();
    return (Success ? EXIT_SUCCESS : EXIT_FAILURE);
}