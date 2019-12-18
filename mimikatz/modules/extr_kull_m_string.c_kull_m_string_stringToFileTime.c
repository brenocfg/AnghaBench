#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  data ;
typedef  scalar_t__ WORD ;
struct TYPE_8__ {int minFields; int idxYear; int idxMonth; int idxDay; int idxHour; int idxMinute; int idxSecond; int /*<<< orphan*/  format; } ;
struct TYPE_7__ {scalar_t__ wSecond; scalar_t__ wMinute; scalar_t__ wHour; scalar_t__ wDay; scalar_t__ wMonth; scalar_t__ wYear; scalar_t__ wMilliseconds; scalar_t__ wDayOfWeek; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  scalar_t__* PULONGLONG ;
typedef  scalar_t__* PFILETIME ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ LONGLONG ;
typedef  TYPE_2__ KIWI_DATETIME_FORMATS ;
typedef  scalar_t__ FILETIME ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ARRAYSIZE (TYPE_2__*) ; 
 int FALSE ; 
 scalar_t__ FileTimeToLocalFileTime (scalar_t__*,scalar_t__*) ; 
 scalar_t__ FileTimeToSystemTime (scalar_t__*,TYPE_1__*) ; 
 int /*<<< orphan*/  GetSystemTimeAsFileTime (scalar_t__*) ; 
 int /*<<< orphan*/  RtlZeroMemory (scalar_t__*,int) ; 
 TYPE_2__* STRING_TO_FILETIME_FORMATS ; 
 int SystemTimeToFileTime (TYPE_1__*,scalar_t__*) ; 
 int swscanf_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 

BOOL kull_m_string_stringToFileTime(LPCWSTR string, PFILETIME filetime)
{
	BOOL status = FALSE;
	const KIWI_DATETIME_FORMATS * cur;
	SYSTEMTIME st;
	FILETIME ft, lft;
	LONGLONG diff;
	WORD i, data[6] = {0};
	int ret;
	
	for(i = 0; (i < ARRAYSIZE(STRING_TO_FILETIME_FORMATS)) && !status; i++)
	{
		cur = STRING_TO_FILETIME_FORMATS + i;
		RtlZeroMemory(data, sizeof(data));
		ret = swscanf_s(string, cur->format, data + 0, data + 1, data + 2, data + 3, data + 4, data + 5);

		if(ret >=cur->minFields)
		{
			if(cur->idxYear && (cur->idxYear <= ret))
			{
				status = data[cur->idxYear - 1] >= 1900;
				if(!status)
					continue;
			}
			
			if(cur->idxMonth && (cur->idxMonth <= ret))
			{
				status = data[cur->idxMonth - 1] <= 12;
				if(!status)
					continue;
			}

			if(cur->idxDay && (cur->idxDay <= ret))
			{
				status = data[cur->idxDay - 1] <= 31;
				if(!status)
					continue;
			}

			if(cur->idxHour && (cur->idxHour <= ret))
			{
				status = data[cur->idxHour - 1] <= 23;
				if(!status)
					continue;
			}

			if(cur->idxMinute && (cur->idxMinute <= ret))
			{
				status = data[cur->idxMinute - 1] <= 59;
				if(!status)
					continue;
			}

			if(cur->idxSecond && (cur->idxSecond <= ret))
			{
				status = data[cur->idxSecond - 1] <= 59;
				if(!status)
					continue;
			}
		}
	}

	if(status)
	{
		status = FALSE;
		i--;
		GetSystemTimeAsFileTime(&ft);
		if(FileTimeToLocalFileTime(&ft, &lft))
		{
			diff = *((PULONGLONG) &lft) - *((PULONGLONG) &ft);
			if(FileTimeToSystemTime(&lft, &st))
			{
				st.wDayOfWeek = 0;
				st.wMilliseconds = 0;

				if(cur->idxYear && (cur->idxYear <= ret))
					st.wYear = data[cur->idxYear - 1];
				if(cur->idxMonth && (cur->idxMonth <= ret))
					st.wMonth = data[cur->idxMonth - 1];
				if(cur->idxDay && (cur->idxDay <= ret))
					st.wDay = data[cur->idxDay - 1];
				if(cur->idxHour && (cur->idxHour <= ret))
					st.wHour = data[cur->idxHour - 1];
				if(cur->idxMinute && (cur->idxMinute <= ret))
					st.wMinute = data[cur->idxMinute - 1];
				if(cur->idxSecond && (cur->idxSecond <= ret))
					st.wSecond = data[cur->idxSecond - 1];

				if(status = SystemTimeToFileTime(&st, &ft))
				{
					*((PULONGLONG) &ft) -= diff;
					*filetime = ft;
				}
			}
		}

	}
	return status;
}