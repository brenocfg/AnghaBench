#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_6__ {int nrFields; int* fieldspec; int* buflen; scalar_t__ textbuf; } ;
struct TYPE_5__ {int /*<<< orphan*/  cx; } ;
typedef  TYPE_1__ SIZE ;
typedef  int /*<<< orphan*/  SHORT ;
typedef  char const* LPCWSTR ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int LCTYPE ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  TYPE_2__ DATETIME_INFO ;

/* Variables and functions */
 int DT_STRING ; 
#define  FULLDAY 149 
#define  FULLMONTH 148 
#define  FULLYEAR 147 
 int /*<<< orphan*/  GetLocaleInfoW (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTextExtentPoint32W (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,TYPE_1__*) ; 
#define  INVALIDFULLYEAR 146 
 int LOCALE_SABBREVDAYNAME1 ; 
 int LOCALE_SABBREVMONTHNAME1 ; 
 int LOCALE_SDAYNAME1 ; 
 int LOCALE_SMONTHNAME1 ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 
#define  ONEDIGIT12HOUR 145 
#define  ONEDIGIT24HOUR 144 
#define  ONEDIGITDAY 143 
#define  ONEDIGITMINUTE 142 
#define  ONEDIGITMONTH 141 
#define  ONEDIGITSECOND 140 
#define  ONEDIGITYEAR 139 
#define  ONELETTERAMPM 138 
#define  THREECHARDAY 137 
#define  THREECHARMONTH 136 
 int /*<<< orphan*/  TRACE (char*,int,int) ; 
#define  TWODIGIT12HOUR 135 
#define  TWODIGIT24HOUR 134 
#define  TWODIGITDAY 133 
#define  TWODIGITMINUTE 132 
#define  TWODIGITMONTH 131 
#define  TWODIGITSECOND 130 
#define  TWODIGITYEAR 129 
#define  TWOLETTERAMPM 128 
 int /*<<< orphan*/  WARN (char*,int,int) ; 
 int /*<<< orphan*/  lstrlenW (char const*) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  strlenW (char const*) ; 

__attribute__((used)) static void
DATETIME_ReturnFieldWidth (const DATETIME_INFO *infoPtr, HDC hdc, int count, SHORT *width)
{
    /* fields are a fixed width, determined by the largest possible string */
    /* presumably, these widths should be language dependent */
    static const WCHAR fld_d1W[] = { '2', 0 };
    static const WCHAR fld_d2W[] = { '2', '2', 0 };
    static const WCHAR fld_d4W[] = { '2', '2', '2', '2', 0 };
    static const WCHAR fld_am1[] = { 'A', 0 };
    static const WCHAR fld_am2[] = { 'A', 'M', 0 };
    int spec;
    WCHAR buffer[80];
    LPCWSTR bufptr;
    SIZE size;

    TRACE ("%d,%d\n", infoPtr->nrFields, count);
    if (count>infoPtr->nrFields || count < 0) {
	WARN ("buffer overrun, have %d want %d\n", infoPtr->nrFields, count);
	return;
    }

    if (!infoPtr->fieldspec) return;

    spec = infoPtr->fieldspec[count];
    if (spec & DT_STRING) {
	int txtlen = infoPtr->buflen[count];

        if (txtlen > 79)
            txtlen = 79;
	memcpy (buffer, infoPtr->textbuf + (spec &~ DT_STRING), txtlen * sizeof(WCHAR));
	buffer[txtlen] = 0;
	bufptr = buffer;
    }
    else {
        switch (spec) {
	    case ONEDIGITDAY:
	    case ONEDIGIT12HOUR:
	    case ONEDIGIT24HOUR:
	    case ONEDIGITSECOND:
	    case ONEDIGITMINUTE:
	    case ONEDIGITMONTH:
	    case ONEDIGITYEAR:
	        /* these seem to use a two byte field */
	    case TWODIGITDAY:
	    case TWODIGIT12HOUR:
	    case TWODIGIT24HOUR:
	    case TWODIGITSECOND:
	    case TWODIGITMINUTE:
	    case TWODIGITMONTH:
	    case TWODIGITYEAR:
	        bufptr = fld_d2W;
	        break;
            case INVALIDFULLYEAR:
	    case FULLYEAR:
	        bufptr = fld_d4W;
	        break;
	    case THREECHARMONTH:
	    case FULLMONTH:
	    case THREECHARDAY:
	    case FULLDAY:
	    {
		static const WCHAR fld_day[] = {'W','e','d','n','e','s','d','a','y',0};
		static const WCHAR fld_abbrday[] = {'W','e','d',0};
		static const WCHAR fld_mon[] = {'S','e','p','t','e','m','b','e','r',0};
		static const WCHAR fld_abbrmon[] = {'D','e','c',0};

		const WCHAR *fall;
		LCTYPE lctype;
		INT i, max_count;
		LONG cx;

		/* choose locale data type and fallback string */
		switch (spec) {
		case THREECHARDAY:
		    fall   = fld_abbrday;
		    lctype = LOCALE_SABBREVDAYNAME1;
		    max_count = 7;
		    break;
		case FULLDAY:
		    fall   = fld_day;
		    lctype = LOCALE_SDAYNAME1;
		    max_count = 7;
		    break;
		case THREECHARMONTH:
		    fall   = fld_abbrmon;
		    lctype = LOCALE_SABBREVMONTHNAME1;
		    max_count = 12;
		    break;
		default: /* FULLMONTH */
		    fall   = fld_mon;
		    lctype = LOCALE_SMONTHNAME1;
		    max_count = 12;
		    break;
		}

		cx = 0;
		for (i = 0; i < max_count; i++)
		{
		    if(GetLocaleInfoW(LOCALE_USER_DEFAULT, lctype + i,
			buffer, lstrlenW(buffer)))
		    {
			GetTextExtentPoint32W(hdc, buffer, lstrlenW(buffer), &size);
			if (size.cx > cx) cx = size.cx;
		    }
		    else /* locale independent fallback on failure */
		    {
		        GetTextExtentPoint32W(hdc, fall, lstrlenW(fall), &size);
			cx = size.cx;
		        break;
		    }
		}
		*width = cx;
		return;
	    }
	    case ONELETTERAMPM:
	        bufptr = fld_am1;
	        break;
	    case TWOLETTERAMPM:
	        bufptr = fld_am2;
	        break;
	    default:
	        bufptr = fld_d1W;
	        break;
        }
    }
    GetTextExtentPoint32W (hdc, bufptr, strlenW(bufptr), &size);
    *width = size.cx;
}