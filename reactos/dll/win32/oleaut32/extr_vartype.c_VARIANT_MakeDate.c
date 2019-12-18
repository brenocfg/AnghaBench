#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int dwCount; int* dwValues; int* dwFlags; int dwParseFlags; } ;
struct TYPE_6__ {int wYear; int wHour; int wMinute; int wSecond; int wDay; int wMonth; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  TYPE_2__ DATEPARSE ;

/* Variables and functions */
 int /*<<< orphan*/  DATE_SWAP (int,int) ; 
 int /*<<< orphan*/  DISP_E_TYPEMISMATCH ; 
 int DP_AM ; 
 int DP_MONTH ; 
 int DP_PM ; 
 int /*<<< orphan*/  GetSystemTime (TYPE_1__*) ; 
 int ORDER_DMY ; 
 int ORDER_MDY ; 
 int ORDER_MYD ; 
 int ORDER_YDM ; 
 int ORDER_YMD ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int,...) ; 
 scalar_t__ VARIANT_IsValidMonthDay (int,int,int) ; 

__attribute__((used)) static inline HRESULT VARIANT_MakeDate(DATEPARSE *dp, DWORD iDate,
                                       DWORD offset, SYSTEMTIME *st)
{
  DWORD dwAllOrders, dwTry, dwCount = 0, v1, v2, v3;

  if (!dp->dwCount)
  {
    v1 = 30; /* Default to (Variant) 0 date part */
    v2 = 12;
    v3 = 1899;
    goto VARIANT_MakeDate_OK;
  }

  v1 = dp->dwValues[offset + 0];
  v2 = dp->dwValues[offset + 1];
  if (dp->dwCount == 2)
  {
    SYSTEMTIME current;
    GetSystemTime(&current);
    v3 = current.wYear;
  }
  else
    v3 = dp->dwValues[offset + 2];

  TRACE("(%d,%d,%d,%d,%d)\n", v1, v2, v3, iDate, offset);

  /* If one number must be a month (Because a month name was given), then only
   * consider orders with the month in that position.
   * If we took the current year as 'v3', then only allow a year in that position.
   */
  if (dp->dwFlags[offset + 0] & DP_MONTH)
  {
    dwAllOrders = ORDER_MDY;
  }
  else if (dp->dwFlags[offset + 1] & DP_MONTH)
  {
    dwAllOrders = ORDER_DMY;
    if (dp->dwCount > 2)
      dwAllOrders |= ORDER_YMD;
  }
  else if (dp->dwCount > 2 && dp->dwFlags[offset + 2] & DP_MONTH)
  {
    dwAllOrders = ORDER_YDM;
  }
  else
  {
    dwAllOrders = ORDER_MDY|ORDER_DMY;
    if (dp->dwCount > 2)
      dwAllOrders |= (ORDER_YMD|ORDER_YDM);
  }

VARIANT_MakeDate_Start:
  TRACE("dwAllOrders is 0x%08x\n", dwAllOrders);

  while (dwAllOrders)
  {
    DWORD dwTemp;

    if (dwCount == 0)
    {
      /* First: Try the order given by iDate */
      switch (iDate)
      {
      case 0:  dwTry = dwAllOrders & ORDER_MDY; break;
      case 1:  dwTry = dwAllOrders & ORDER_DMY; break;
      default: dwTry = dwAllOrders & ORDER_YMD; break;
      }
    }
    else if (dwCount == 1)
    {
      /* Second: Try all the orders compatible with iDate */
      switch (iDate)
      {
      case 0:  dwTry = dwAllOrders & ~(ORDER_DMY|ORDER_YDM); break;
      case 1:  dwTry = dwAllOrders & ~(ORDER_MDY|ORDER_YDM|ORDER_MYD); break;
      default: dwTry = dwAllOrders & ~(ORDER_DMY|ORDER_YDM); break;
      }
    }
    else
    {
      /* Finally: Try any remaining orders */
      dwTry = dwAllOrders;
    }

    TRACE("Attempt %d, dwTry is 0x%08x\n", dwCount, dwTry);

    dwCount++;
    if (!dwTry)
      continue;

#define DATE_SWAP(x,y) do { dwTemp = x; x = y; y = dwTemp; } while (0)

    if (dwTry & ORDER_MDY)
    {
      if (VARIANT_IsValidMonthDay(v2,v1,v3))
      {
        DATE_SWAP(v1,v2);
        goto VARIANT_MakeDate_OK;
      }
      dwAllOrders &= ~ORDER_MDY;
    }
    if (dwTry & ORDER_YMD)
    {
      if (VARIANT_IsValidMonthDay(v3,v2,v1))
      {
        DATE_SWAP(v1,v3);
        goto VARIANT_MakeDate_OK;
      }
      dwAllOrders &= ~ORDER_YMD;
    }
    if (dwTry & ORDER_YDM)
    {
      if (VARIANT_IsValidMonthDay(v2,v3,v1))
      {
        DATE_SWAP(v1,v2);
        DATE_SWAP(v2,v3);
        goto VARIANT_MakeDate_OK;
      }
      dwAllOrders &= ~ORDER_YDM;
    }
    if (dwTry & ORDER_DMY)
    {
      if (VARIANT_IsValidMonthDay(v1,v2,v3))
        goto VARIANT_MakeDate_OK;
      dwAllOrders &= ~ORDER_DMY;
    }
    if (dwTry & ORDER_MYD)
    {
      /* Only occurs if we are trying a 2 year date as M/Y not D/M */
      if (VARIANT_IsValidMonthDay(v3,v1,v2))
      {
        DATE_SWAP(v1,v3);
        DATE_SWAP(v2,v3);
        goto VARIANT_MakeDate_OK;
      }
      dwAllOrders &= ~ORDER_MYD;
    }
  }

  if (dp->dwCount == 2)
  {
    /* We couldn't make a date as D/M or M/D, so try M/Y or Y/M */
    v3 = 1; /* 1st of the month */
    dwAllOrders = ORDER_YMD|ORDER_MYD;
    dp->dwCount = 0; /* Don't return to this code path again */
    dwCount = 0;
    goto VARIANT_MakeDate_Start;
  }

  /* No valid dates were able to be constructed */
  return DISP_E_TYPEMISMATCH;

VARIANT_MakeDate_OK:

  /* Check that the time part is ok */
  if (st->wHour > 23 || st->wMinute > 59 || st->wSecond > 59)
    return DISP_E_TYPEMISMATCH;

  TRACE("Time %d %d %d\n", st->wHour, st->wMinute, st->wSecond);
  if (st->wHour < 12 && (dp->dwParseFlags & DP_PM))
    st->wHour += 12;
  else if (st->wHour == 12 && (dp->dwParseFlags & DP_AM))
    st->wHour = 0;
  TRACE("Time %d %d %d\n", st->wHour, st->wMinute, st->wSecond);

  st->wDay = v1;
  st->wMonth = v2;
  /* FIXME: For 2 digit dates, I'm not sure if 30 is hard coded or not. It may
   * be retrieved from:
   * HKCU\Control Panel\International\Calendars\TwoDigitYearMax
   * But Wine doesn't have/use that key as at the time of writing.
   */
  st->wYear = v3 < 30 ? 2000 + v3 : v3 < 100 ? 1900 + v3 : v3;
  TRACE("Returning date %d/%d/%d\n", v1, v2, st->wYear);
  return S_OK;
}