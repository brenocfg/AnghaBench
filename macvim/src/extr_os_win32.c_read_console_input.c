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
struct TYPE_5__ {scalar_t__ EventType; } ;
typedef  int* LPDWORD ;
typedef  TYPE_1__ INPUT_RECORD ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PeekConsoleInput (int /*<<< orphan*/ ,TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  ReadConsoleInput (int /*<<< orphan*/ ,TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WINDOW_BUFFER_SIZE_EVENT ; 
 int /*<<< orphan*/  win8_or_later ; 

__attribute__((used)) static BOOL
read_console_input(
    HANDLE	    hInput,
    INPUT_RECORD    *lpBuffer,
    DWORD	    nLength,
    LPDWORD	    lpEvents)
{
    enum
    {
	IRSIZE = 10
    };
    static INPUT_RECORD s_irCache[IRSIZE];
    static DWORD s_dwIndex = 0;
    static DWORD s_dwMax = 0;
    DWORD dwEvents;
    int head;
    int tail;
    int i;

    if (!win8_or_later)
    {
	if (nLength == -1)
	    return PeekConsoleInput(hInput, lpBuffer, 1, lpEvents);
	return ReadConsoleInput(hInput, lpBuffer, 1, &dwEvents);
    }

    if (s_dwMax == 0)
    {
	if (nLength == -1)
	    return PeekConsoleInput(hInput, lpBuffer, 1, lpEvents);
	if (!ReadConsoleInput(hInput, s_irCache, IRSIZE, &dwEvents))
	    return FALSE;
	s_dwIndex = 0;
	s_dwMax = dwEvents;
	if (dwEvents == 0)
	{
	    *lpEvents = 0;
	    return TRUE;
	}

	if (s_dwMax > 1)
	{
	    head = 0;
	    tail = s_dwMax - 1;
	    while (head != tail)
	    {
		if (s_irCache[head].EventType == WINDOW_BUFFER_SIZE_EVENT
			&& s_irCache[head + 1].EventType
						  == WINDOW_BUFFER_SIZE_EVENT)
		{
		    /* Remove duplicate event to avoid flicker. */
		    for (i = head; i < tail; ++i)
			s_irCache[i] = s_irCache[i + 1];
		    --tail;
		    continue;
		}
		head++;
	    }
	    s_dwMax = tail + 1;
	}
    }

    *lpBuffer = s_irCache[s_dwIndex];
    if (nLength != -1 && ++s_dwIndex >= s_dwMax)
	s_dwMax = 0;
    *lpEvents = 1;
    return TRUE;
}