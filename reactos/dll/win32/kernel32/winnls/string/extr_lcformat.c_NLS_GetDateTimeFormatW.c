#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  st ;
typedef  int /*<<< orphan*/  buff ;
typedef  char WCHAR ;
struct TYPE_25__ {char* szShortAM; char* szShortPM; } ;
struct TYPE_24__ {int wYear; int /*<<< orphan*/  szEraName; } ;
struct TYPE_23__ {int wYear; int wMonth; int wDay; int wHour; int wMinute; int wSecond; int /*<<< orphan*/  wDayOfWeek; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  TYPE_2__* PCJAPANESE_ERA ;
typedef  TYPE_3__ NLS_FORMAT_NODE ;
typedef  char* LPWSTR ;
typedef  char* LPCWSTR ;
typedef  int /*<<< orphan*/  LCID ;
typedef  size_t INT ;
typedef  int /*<<< orphan*/  FILETIME ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int DATE_DATEVARSONLY ; 
 int DATE_FORMAT_FLAGS ; 
#define  DATE_LONGDATE 130 
 int DATE_LTRREADING ; 
 int DATE_RTLREADING ; 
#define  DATE_SHORTDATE 129 
 int DATE_USE_ALT_CALENDAR ; 
#define  DATE_YEARMONTH 128 
 int /*<<< orphan*/  ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  ERROR_INVALID_FLAGS ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  FileTimeToSystemTime (int /*<<< orphan*/ *,TYPE_1__*) ; 
 char* GetAM (TYPE_3__ const*) ; 
 char* GetGenitiveMonth (TYPE_3__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLocalTime (TYPE_1__*) ; 
 char* GetLongDate (TYPE_3__ const*) ; 
 char* GetLongDay (TYPE_3__ const*,int) ; 
 char* GetLongMonth (TYPE_3__ const*,int /*<<< orphan*/ ) ; 
 char* GetPM (TYPE_3__ const*) ; 
 char* GetShortDate (TYPE_3__ const*) ; 
 char* GetShortDay (TYPE_3__ const*,int) ; 
 char* GetShortMonth (TYPE_3__ const*,int /*<<< orphan*/ ) ; 
 char* GetTime (TYPE_3__ const*) ; 
 char* GetYearMonth (TYPE_3__ const*) ; 
 int /*<<< orphan*/  IS_LCID_JAPANESE (int /*<<< orphan*/ ) ; 
 scalar_t__ IsDateFmtChar (char) ; 
 scalar_t__ IsLiteralMarker (char) ; 
 scalar_t__ IsTimeFmtChar (char) ; 
 TYPE_2__* JapaneseEra_Find (TYPE_1__ const*) ; 
 int /*<<< orphan*/  JapaneseEra_IsFirstYearGannen () ; 
 TYPE_3__* NLS_GetFormats (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlStringCbCopyW (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemTimeToFileTime (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int TIME_FORCE24HOURFORMAT ; 
 int TIME_FORMAT_FLAGS ; 
 int TIME_NOMINUTESORSECONDS ; 
 int TIME_NOSECONDS ; 
 int TIME_NOTIMEMARKER ; 
 int TIME_TIMEVARSONLY ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintfW (char*,int /*<<< orphan*/ ,char const*,int,int) ; 
 int strlenW (char*) ; 

__attribute__((used)) static INT NLS_GetDateTimeFormatW(LCID lcid, DWORD dwFlags,
                                  const SYSTEMTIME* lpTime, LPCWSTR lpFormat,
                                  LPWSTR lpStr, INT cchOut)
{
  const NLS_FORMAT_NODE *node;
  SYSTEMTIME st;
  INT cchWritten = 0;
  INT lastFormatPos = 0;
  BOOL bSkipping = FALSE; /* Skipping text around marker? */
  BOOL d_dd_formatted = FALSE; /* previous formatted part was for d or dd */

  /* Verify our arguments */
  if ((cchOut && !lpStr) || !(node = NLS_GetFormats(lcid, dwFlags)))
    goto invalid_parameter;

  if (dwFlags & ~(DATE_DATEVARSONLY|TIME_TIMEVARSONLY))
  {
    if (lpFormat &&
        ((dwFlags & DATE_DATEVARSONLY && dwFlags & ~DATE_FORMAT_FLAGS) ||
         (dwFlags & TIME_TIMEVARSONLY && dwFlags & ~TIME_FORMAT_FLAGS)))
    {
      goto invalid_flags;
    }

    if (dwFlags & DATE_DATEVARSONLY)
    {
      if ((dwFlags & (DATE_LTRREADING|DATE_RTLREADING)) == (DATE_LTRREADING|DATE_RTLREADING))
        goto invalid_flags;
      else if (dwFlags & (DATE_LTRREADING|DATE_RTLREADING))
        FIXME("Unsupported flags: DATE_LTRREADING/DATE_RTLREADING\n");

      switch (dwFlags & (DATE_SHORTDATE|DATE_LONGDATE|DATE_YEARMONTH))
      {
      case 0:
        break;
      case DATE_SHORTDATE:
      case DATE_LONGDATE:
      case DATE_YEARMONTH:
        if (lpFormat)
          goto invalid_flags;
        break;
      default:
        goto invalid_flags;
      }
    }
  }

  if (!lpFormat)
  {
    /* Use the appropriate default format */
    if (dwFlags & DATE_DATEVARSONLY)
    {
      if (dwFlags & DATE_YEARMONTH)
        lpFormat = GetYearMonth(node);
      else if (dwFlags & DATE_LONGDATE)
        lpFormat = GetLongDate(node);
      else
        lpFormat = GetShortDate(node);
    }
    else
      lpFormat = GetTime(node);
  }

  if (!lpTime)
  {
    GetLocalTime(&st); /* Default to current time */
    lpTime = &st;
  }
  else
  {
    if (dwFlags & DATE_DATEVARSONLY)
    {
      FILETIME ftTmp;

      /* Verify the date and correct the D.O.W. if needed */
      memset(&st, 0, sizeof(st));
      st.wYear = lpTime->wYear;
      st.wMonth = lpTime->wMonth;
      st.wDay = lpTime->wDay;

      if (st.wDay > 31 || st.wMonth > 12 || !SystemTimeToFileTime(&st, &ftTmp))
        goto invalid_parameter;

      FileTimeToSystemTime(&ftTmp, &st);
      lpTime = &st;
    }

    if (dwFlags & TIME_TIMEVARSONLY)
    {
      /* Verify the time */
      if (lpTime->wHour > 24 || lpTime->wMinute > 59 || lpTime->wSecond > 59)
        goto invalid_parameter;
    }
  }

  /* Format the output */
  while (*lpFormat)
  {
    if (IsLiteralMarker(*lpFormat))
    {
      /* Start of a literal string */
      lpFormat++;

      /* Loop until the end of the literal marker or end of the string */
      while (*lpFormat)
      {
        if (IsLiteralMarker(*lpFormat))
        {
          lpFormat++;
          if (!IsLiteralMarker(*lpFormat))
            break; /* Terminating literal marker */
        }

        if (!cchOut)
          cchWritten++;   /* Count size only */
        else if (cchWritten >= cchOut)
          goto overrun;
        else if (!bSkipping)
        {
          lpStr[cchWritten] = *lpFormat;
          cchWritten++;
        }
        lpFormat++;
      }
    }
    else if ((dwFlags & DATE_DATEVARSONLY && IsDateFmtChar(*lpFormat)) ||
             (dwFlags & TIME_TIMEVARSONLY && IsTimeFmtChar(*lpFormat)))
    {
      WCHAR buff[32], fmtChar;
      LPCWSTR szAdd = NULL;
      DWORD dwVal = 0;
      int   count = 0, dwLen;

      bSkipping = FALSE;

      fmtChar = *lpFormat;
      while (*lpFormat == fmtChar)
      {
        count++;
        lpFormat++;
      }
      buff[0] = '\0';

      if (fmtChar != 'M') d_dd_formatted = FALSE;
      switch(fmtChar)
      {
      case 'd':
        if (count >= 4)
          szAdd = GetLongDay(node, (lpTime->wDayOfWeek + 6) % 7);
        else if (count == 3)
          szAdd = GetShortDay(node, (lpTime->wDayOfWeek + 6) % 7);
        else
        {
          dwVal = lpTime->wDay;
          szAdd = buff;
          d_dd_formatted = TRUE;
        }
        break;

      case 'M':
        if (count >= 4)
        {
          LPCWSTR genitive = GetGenitiveMonth(node, lpTime->wMonth - 1);
          if (genitive)
          {
            if (d_dd_formatted)
            {
              szAdd = genitive;
              break;
            }
            else
            {
              LPCWSTR format = lpFormat;
              /* Look forward now, if next format pattern is for day genitive
                 name should be used */
              while (*format)
              {
                /* Skip parts within markers */
                if (IsLiteralMarker(*format))
                {
                  ++format;
                  while (*format)
                  {
                    if (IsLiteralMarker(*format))
                    {
                      ++format;
                      if (!IsLiteralMarker(*format)) break;
                    }
                  }
                }
                if (*format != ' ') break;
                ++format;
              }
              /* Only numeric day form matters */
              if (*format == 'd')
              {
                INT dcount = 1;
                while (*++format == 'd') dcount++;
                if (dcount < 3)
                {
                  szAdd = genitive;
                  break;
                }
              }
            }
          }
          szAdd = GetLongMonth(node, lpTime->wMonth - 1);
        }
        else if (count == 3)
          szAdd = GetShortMonth(node, lpTime->wMonth - 1);
        else
        {
          dwVal = lpTime->wMonth;
          szAdd = buff;
        }
        break;

      case 'y':
#ifdef __REACTOS__
        if (IS_LCID_JAPANESE(lcid) && (dwFlags & DATE_USE_ALT_CALENDAR))
        {
            PCJAPANESE_ERA pEra = JapaneseEra_Find(lpTime);
            if (pEra)
            {
                if (count >= 2)
                {
                    count = 2;
                }

                dwVal = lpTime->wYear - pEra->wYear + 1;

                if (dwVal == 1 && JapaneseEra_IsFirstYearGannen())
                {
                    // Gan of 'Gannen'
                    buff[0] = 0x5143;
                    buff[1] = 0;
                }
                szAdd = buff;
                break;
            }
            SetLastError(ERROR_INVALID_PARAMETER);
            return 0;
        }
#endif
        if (count >= 4)
        {
          count = 4;
          dwVal = lpTime->wYear;
        }
        else
        {
          count = count > 2 ? 2 : count;
          dwVal = lpTime->wYear % 100;
        }
        szAdd = buff;
        break;

      case 'g':
#ifdef __REACTOS__
        if (IS_LCID_JAPANESE(lcid))
        {
            if (dwFlags & DATE_USE_ALT_CALENDAR)
            {
                PCJAPANESE_ERA pEra = JapaneseEra_Find(lpTime);
                if (pEra)
                {
                    RtlStringCbCopyW(buff, sizeof(buff), pEra->szEraName);
                    szAdd = buff;
                    break;
                }
                SetLastError(ERROR_INVALID_PARAMETER);
                return 0;
            }
            else
            {
                /* Seireki */
                buff[0] = 0x897F;
                buff[1] = 0x66A6;
                buff[2] = 0;
                szAdd = buff;
                break;
            }
        }
#endif
        if (count == 2)
        {
          /* FIXME: Our GetCalendarInfo() does not yet support CAL_SERASTRING.
           *        When it is fixed, this string should be cached in 'node'.
           */
          FIXME("Should be using GetCalendarInfo(CAL_SERASTRING), defaulting to 'AD'\n");
          buff[0] = 'A'; buff[1] = 'D'; buff[2] = '\0';
        }
        else
        {
          buff[0] = 'g'; buff[1] = '\0'; /* Add a literal 'g' */
        }
        szAdd = buff;
        break;

      case 'h':
        if (!(dwFlags & TIME_FORCE24HOURFORMAT))
        {
          count = count > 2 ? 2 : count;
          dwVal = lpTime->wHour == 0 ? 12 : (lpTime->wHour - 1) % 12 + 1;
          szAdd = buff;
          break;
        }
        /* .. fall through if we are forced to output in 24 hour format */

      case 'H':
        count = count > 2 ? 2 : count;
        dwVal = lpTime->wHour;
        szAdd = buff;
        break;

      case 'm':
        if (dwFlags & TIME_NOMINUTESORSECONDS)
        {
          cchWritten = lastFormatPos; /* Skip */
          bSkipping = TRUE;
        }
        else
        {
          count = count > 2 ? 2 : count;
          dwVal = lpTime->wMinute;
          szAdd = buff;
        }
        break;

      case 's':
        if (dwFlags & (TIME_NOSECONDS|TIME_NOMINUTESORSECONDS))
        {
          cchWritten = lastFormatPos; /* Skip */
          bSkipping = TRUE;
        }
        else
        {
          count = count > 2 ? 2 : count;
          dwVal = lpTime->wSecond;
          szAdd = buff;
        }
        break;

      case 't':
        if (dwFlags & TIME_NOTIMEMARKER)
        {
          cchWritten = lastFormatPos; /* Skip */
          bSkipping = TRUE;
        }
        else
        {
          if (count == 1)
            szAdd = lpTime->wHour < 12 ? node->szShortAM : node->szShortPM;
          else
            szAdd = lpTime->wHour < 12 ? GetAM(node) : GetPM(node);
        }
        break;
      }

      if (szAdd == buff && buff[0] == '\0')
      {
        static const WCHAR fmtW[] = {'%','.','*','d',0};
        /* We have a numeric value to add */
        snprintfW(buff, ARRAY_SIZE(buff), fmtW, count, dwVal);
      }

      dwLen = szAdd ? strlenW(szAdd) : 0;

      if (cchOut && dwLen)
      {
        if (cchWritten + dwLen < cchOut)
          memcpy(lpStr + cchWritten, szAdd, dwLen * sizeof(WCHAR));
        else
        {
          memcpy(lpStr + cchWritten, szAdd, (cchOut - cchWritten) * sizeof(WCHAR));
          goto overrun;
        }
      }
      cchWritten += dwLen;
      lastFormatPos = cchWritten; /* Save position of last output format text */
    }
    else
    {
      /* Literal character */
      if (!cchOut)
        cchWritten++;   /* Count size only */
      else if (cchWritten >= cchOut)
        goto overrun;
      else if (!bSkipping || *lpFormat == ' ')
      {
        lpStr[cchWritten] = *lpFormat;
        cchWritten++;
      }
      lpFormat++;
    }
  }

  /* Final string terminator and sanity check */
  if (cchOut)
  {
   if (cchWritten >= cchOut)
     goto overrun;
   else
     lpStr[cchWritten] = '\0';
  }
  cchWritten++; /* Include terminating NUL */

  TRACE("returning length=%d, output=%s\n", cchWritten, debugstr_w(lpStr));
  return cchWritten;

overrun:
  TRACE("returning 0, (ERROR_INSUFFICIENT_BUFFER)\n");
  SetLastError(ERROR_INSUFFICIENT_BUFFER);
  return 0;

invalid_parameter:
  SetLastError(ERROR_INVALID_PARAMETER);
  return 0;

invalid_flags:
  SetLastError(ERROR_INVALID_FLAGS);
  return 0;
}