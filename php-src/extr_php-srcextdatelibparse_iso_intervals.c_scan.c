#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uchar ;
struct TYPE_9__ {void* s; void* i; void* h; void* d; void* m; void* y; } ;
typedef  TYPE_3__ timelib_time ;
typedef  int timelib_sll ;
typedef  char YYCTYPE ;
struct TYPE_10__ {int have_period; int have_date; int have_end_date; int have_begin_date; int have_recurrences; void* recurrences; TYPE_3__* begin; TYPE_3__* end; TYPE_2__* period; int /*<<< orphan*/  line; int /*<<< orphan*/ * pos; TYPE_1__* errors; scalar_t__ len; int /*<<< orphan*/ * tok; int /*<<< orphan*/ * cur; } ;
struct TYPE_8__ {int y; int d; int h; int s; int i; int m; } ;
struct TYPE_7__ {int /*<<< orphan*/  error_count; } ;
typedef  TYPE_4__ Scanner ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_OUTPUT (char*) ; 
 int /*<<< orphan*/  TIMELIB_DEINIT ; 
 int /*<<< orphan*/  TIMELIB_INIT ; 
 int TIMELIB_ISO_DATE ; 
 int TIMELIB_PERIOD ; 
 char* YYCURSOR ; 
 int /*<<< orphan*/  YYDEBUG (int,char) ; 
 int /*<<< orphan*/  YYFILL (int) ; 
 char* YYLIMIT ; 
 char* YYMARKER ; 
 int /*<<< orphan*/  add_error (TYPE_4__*,char*) ; 
 void* timelib_get_nr (char**,int) ; 
 void* timelib_get_unsigned_nr (char**,int) ; 

__attribute__((used)) static int scan(Scanner *s)
{
	uchar *cursor = s->cur;
	char *str, *ptr = NULL;

std:
	s->tok = cursor;
	s->len = 0;
#line 202 "parse_iso_intervals.re"



#line 182 "<stdout>"
{
	YYCTYPE yych;
	unsigned int yyaccept = 0;
	static const unsigned char yybm[] = {
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
	};
	YYDEBUG(0, *YYCURSOR);
	if ((YYLIMIT - YYCURSOR) < 20) YYFILL(20);
	yych = *YYCURSOR;
	if (yych <= ',') {
		if (yych <= '\n') {
			if (yych <= 0x00) goto yy9;
			if (yych <= 0x08) goto yy11;
			if (yych <= '\t') goto yy7;
			goto yy9;
		} else {
			if (yych == ' ') goto yy7;
			if (yych <= '+') goto yy11;
			goto yy7;
		}
	} else {
		if (yych <= 'O') {
			if (yych <= '-') goto yy11;
			if (yych <= '/') goto yy7;
			if (yych <= '9') goto yy4;
			goto yy11;
		} else {
			if (yych <= 'P') goto yy5;
			if (yych != 'R') goto yy11;
		}
	}
	YYDEBUG(2, *YYCURSOR);
	++YYCURSOR;
	if ((yych = *YYCURSOR) <= '/') goto yy3;
	if (yych <= '9') goto yy98;
yy3:
	YYDEBUG(3, *YYCURSOR);
#line 315 "parse_iso_intervals.re"
	{
		add_error(s, "Unexpected character");
		goto std;
	}
#line 256 "<stdout>"
yy4:
	YYDEBUG(4, *YYCURSOR);
	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych <= '/') goto yy3;
	if (yych <= '9') goto yy59;
	goto yy3;
yy5:
	YYDEBUG(5, *YYCURSOR);
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych <= '/') goto yy6;
	if (yych <= '9') goto yy12;
	if (yych == 'T') goto yy14;
yy6:
	YYDEBUG(6, *YYCURSOR);
#line 242 "parse_iso_intervals.re"
	{
		timelib_sll nr;
		int         in_time = 0;
		DEBUG_OUTPUT("period");
		TIMELIB_INIT;
		ptr++;
		do {
			if ( *ptr == 'T' ) {
				in_time = 1;
				ptr++;
			}
			if ( *ptr == '\0' ) {
				add_error(s, "Missing expected time part");
				break;
			}

			nr = timelib_get_unsigned_nr((char **) &ptr, 12);
			switch (*ptr) {
				case 'Y': s->period->y = nr; break;
				case 'W': s->period->d = nr * 7; break;
				case 'D': s->period->d = nr; break;
				case 'H': s->period->h = nr; break;
				case 'S': s->period->s = nr; break;
				case 'M':
					if (in_time) {
						s->period->i = nr;
					} else {
						s->period->m = nr;
					}
					break;
				default:
					add_error(s, "Undefined period specifier");
					break;
			}
			ptr++;
		} while (!s->errors->error_count && *ptr);
		s->have_period = 1;
		TIMELIB_DEINIT;
		return TIMELIB_PERIOD;
	}
#line 314 "<stdout>"
yy7:
	YYDEBUG(7, *YYCURSOR);
	++YYCURSOR;
	YYDEBUG(8, *YYCURSOR);
#line 304 "parse_iso_intervals.re"
	{
		goto std;
	}
#line 323 "<stdout>"
yy9:
	YYDEBUG(9, *YYCURSOR);
	++YYCURSOR;
	YYDEBUG(10, *YYCURSOR);
#line 309 "parse_iso_intervals.re"
	{
		s->pos = cursor; s->line++;
		goto std;
	}
#line 333 "<stdout>"
yy11:
	YYDEBUG(11, *YYCURSOR);
	yych = *++YYCURSOR;
	goto yy3;
yy12:
	YYDEBUG(12, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= 'L') {
		if (yych <= '9') {
			if (yych >= '0') goto yy25;
		} else {
			if (yych == 'D') goto yy24;
		}
	} else {
		if (yych <= 'W') {
			if (yych <= 'M') goto yy27;
			if (yych >= 'W') goto yy26;
		} else {
			if (yych == 'Y') goto yy28;
		}
	}
yy13:
	YYDEBUG(13, *YYCURSOR);
	YYCURSOR = YYMARKER;
	if (yyaccept == 0) {
		goto yy3;
	} else {
		goto yy6;
	}
yy14:
	YYDEBUG(14, *YYCURSOR);
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yybm[0+yych] & 128) {
		goto yy15;
	}
	goto yy6;
yy15:
	YYDEBUG(15, *YYCURSOR);
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
	YYDEBUG(16, *YYCURSOR);
	if (yybm[0+yych] & 128) {
		goto yy15;
	}
	if (yych <= 'L') {
		if (yych == 'H') goto yy19;
		goto yy13;
	} else {
		if (yych <= 'M') goto yy18;
		if (yych != 'S') goto yy13;
	}
yy17:
	YYDEBUG(17, *YYCURSOR);
	yych = *++YYCURSOR;
	goto yy6;
yy18:
	YYDEBUG(18, *YYCURSOR);
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych <= '/') goto yy6;
	if (yych <= '9') goto yy22;
	goto yy6;
yy19:
	YYDEBUG(19, *YYCURSOR);
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych <= '/') goto yy6;
	if (yych >= ':') goto yy6;
yy20:
	YYDEBUG(20, *YYCURSOR);
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
	YYDEBUG(21, *YYCURSOR);
	if (yych <= 'L') {
		if (yych <= '/') goto yy13;
		if (yych <= '9') goto yy20;
		goto yy13;
	} else {
		if (yych <= 'M') goto yy18;
		if (yych == 'S') goto yy17;
		goto yy13;
	}
yy22:
	YYDEBUG(22, *YYCURSOR);
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	YYDEBUG(23, *YYCURSOR);
	if (yych <= '/') goto yy13;
	if (yych <= '9') goto yy22;
	if (yych == 'S') goto yy17;
	goto yy13;
yy24:
	YYDEBUG(24, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych == 'T') goto yy14;
	goto yy6;
yy25:
	YYDEBUG(25, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= 'L') {
		if (yych <= '9') {
			if (yych <= '/') goto yy13;
			goto yy35;
		} else {
			if (yych == 'D') goto yy24;
			goto yy13;
		}
	} else {
		if (yych <= 'W') {
			if (yych <= 'M') goto yy27;
			if (yych <= 'V') goto yy13;
		} else {
			if (yych == 'Y') goto yy28;
			goto yy13;
		}
	}
yy26:
	YYDEBUG(26, *YYCURSOR);
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych <= '/') goto yy6;
	if (yych <= '9') goto yy33;
	if (yych == 'T') goto yy14;
	goto yy6;
yy27:
	YYDEBUG(27, *YYCURSOR);
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych <= '/') goto yy6;
	if (yych <= '9') goto yy31;
	if (yych == 'T') goto yy14;
	goto yy6;
yy28:
	YYDEBUG(28, *YYCURSOR);
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych <= '/') goto yy6;
	if (yych <= '9') goto yy29;
	if (yych == 'T') goto yy14;
	goto yy6;
yy29:
	YYDEBUG(29, *YYCURSOR);
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 3) YYFILL(3);
	yych = *YYCURSOR;
	YYDEBUG(30, *YYCURSOR);
	if (yych <= 'D') {
		if (yych <= '/') goto yy13;
		if (yych <= '9') goto yy29;
		if (yych <= 'C') goto yy13;
		goto yy24;
	} else {
		if (yych <= 'M') {
			if (yych <= 'L') goto yy13;
			goto yy27;
		} else {
			if (yych == 'W') goto yy26;
			goto yy13;
		}
	}
yy31:
	YYDEBUG(31, *YYCURSOR);
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 3) YYFILL(3);
	yych = *YYCURSOR;
	YYDEBUG(32, *YYCURSOR);
	if (yych <= 'C') {
		if (yych <= '/') goto yy13;
		if (yych <= '9') goto yy31;
		goto yy13;
	} else {
		if (yych <= 'D') goto yy24;
		if (yych == 'W') goto yy26;
		goto yy13;
	}
yy33:
	YYDEBUG(33, *YYCURSOR);
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 3) YYFILL(3);
	yych = *YYCURSOR;
	YYDEBUG(34, *YYCURSOR);
	if (yych <= '/') goto yy13;
	if (yych <= '9') goto yy33;
	if (yych == 'D') goto yy24;
	goto yy13;
yy35:
	YYDEBUG(35, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= 'L') {
		if (yych <= '9') {
			if (yych <= '/') goto yy13;
		} else {
			if (yych == 'D') goto yy24;
			goto yy13;
		}
	} else {
		if (yych <= 'W') {
			if (yych <= 'M') goto yy27;
			if (yych <= 'V') goto yy13;
			goto yy26;
		} else {
			if (yych == 'Y') goto yy28;
			goto yy13;
		}
	}
	YYDEBUG(36, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych != '-') goto yy39;
	YYDEBUG(37, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '0') goto yy40;
	if (yych <= '1') goto yy41;
	goto yy13;
yy38:
	YYDEBUG(38, *YYCURSOR);
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 3) YYFILL(3);
	yych = *YYCURSOR;
yy39:
	YYDEBUG(39, *YYCURSOR);
	if (yych <= 'L') {
		if (yych <= '9') {
			if (yych <= '/') goto yy13;
			goto yy38;
		} else {
			if (yych == 'D') goto yy24;
			goto yy13;
		}
	} else {
		if (yych <= 'W') {
			if (yych <= 'M') goto yy27;
			if (yych <= 'V') goto yy13;
			goto yy26;
		} else {
			if (yych == 'Y') goto yy28;
			goto yy13;
		}
	}
yy40:
	YYDEBUG(40, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '9') goto yy42;
	goto yy13;
yy41:
	YYDEBUG(41, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych >= '3') goto yy13;
yy42:
	YYDEBUG(42, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych != '-') goto yy13;
	YYDEBUG(43, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '0') goto yy44;
	if (yych <= '2') goto yy45;
	if (yych <= '3') goto yy46;
	goto yy13;
yy44:
	YYDEBUG(44, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '9') goto yy47;
	goto yy13;
yy45:
	YYDEBUG(45, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '9') goto yy47;
	goto yy13;
yy46:
	YYDEBUG(46, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych >= '2') goto yy13;
yy47:
	YYDEBUG(47, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych != 'T') goto yy13;
	YYDEBUG(48, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '1') goto yy49;
	if (yych <= '2') goto yy50;
	goto yy13;
yy49:
	YYDEBUG(49, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '9') goto yy51;
	goto yy13;
yy50:
	YYDEBUG(50, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych >= '5') goto yy13;
yy51:
	YYDEBUG(51, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych != ':') goto yy13;
	YYDEBUG(52, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych >= '6') goto yy13;
	YYDEBUG(53, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych >= ':') goto yy13;
	YYDEBUG(54, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych != ':') goto yy13;
	YYDEBUG(55, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych >= '6') goto yy13;
	YYDEBUG(56, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych >= ':') goto yy13;
	YYDEBUG(57, *YYCURSOR);
	++YYCURSOR;
	YYDEBUG(58, *YYCURSOR);
#line 284 "parse_iso_intervals.re"
	{
		DEBUG_OUTPUT("combinedrep");
		TIMELIB_INIT;
		s->period->y = timelib_get_unsigned_nr((char **) &ptr, 4);
		ptr++;
		s->period->m = timelib_get_unsigned_nr((char **) &ptr, 2);
		ptr++;
		s->period->d = timelib_get_unsigned_nr((char **) &ptr, 2);
		ptr++;
		s->period->h = timelib_get_unsigned_nr((char **) &ptr, 2);
		ptr++;
		s->period->i = timelib_get_unsigned_nr((char **) &ptr, 2);
		ptr++;
		s->period->s = timelib_get_unsigned_nr((char **) &ptr, 2);
		s->have_period = 1;
		TIMELIB_DEINIT;
		return TIMELIB_PERIOD;
	}
#line 682 "<stdout>"
yy59:
	YYDEBUG(59, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych >= ':') goto yy13;
	YYDEBUG(60, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych >= ':') goto yy13;
	YYDEBUG(61, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') {
		if (yych == '-') goto yy64;
		goto yy13;
	} else {
		if (yych <= '0') goto yy62;
		if (yych <= '1') goto yy63;
		goto yy13;
	}
yy62:
	YYDEBUG(62, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '0') goto yy13;
	if (yych <= '9') goto yy85;
	goto yy13;
yy63:
	YYDEBUG(63, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '2') goto yy85;
	goto yy13;
yy64:
	YYDEBUG(64, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '0') goto yy65;
	if (yych <= '1') goto yy66;
	goto yy13;
yy65:
	YYDEBUG(65, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '0') goto yy13;
	if (yych <= '9') goto yy67;
	goto yy13;
yy66:
	YYDEBUG(66, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych >= '3') goto yy13;
yy67:
	YYDEBUG(67, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych != '-') goto yy13;
	YYDEBUG(68, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '0') goto yy69;
	if (yych <= '2') goto yy70;
	if (yych <= '3') goto yy71;
	goto yy13;
yy69:
	YYDEBUG(69, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '0') goto yy13;
	if (yych <= '9') goto yy72;
	goto yy13;
yy70:
	YYDEBUG(70, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '9') goto yy72;
	goto yy13;
yy71:
	YYDEBUG(71, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych >= '2') goto yy13;
yy72:
	YYDEBUG(72, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych != 'T') goto yy13;
	YYDEBUG(73, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '1') goto yy74;
	if (yych <= '2') goto yy75;
	goto yy13;
yy74:
	YYDEBUG(74, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '9') goto yy76;
	goto yy13;
yy75:
	YYDEBUG(75, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych >= '5') goto yy13;
yy76:
	YYDEBUG(76, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych != ':') goto yy13;
	YYDEBUG(77, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych >= '6') goto yy13;
	YYDEBUG(78, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych >= ':') goto yy13;
	YYDEBUG(79, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych != ':') goto yy13;
	YYDEBUG(80, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych >= '6') goto yy13;
	YYDEBUG(81, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych >= ':') goto yy13;
	YYDEBUG(82, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych != 'Z') goto yy13;
yy83:
	YYDEBUG(83, *YYCURSOR);
	++YYCURSOR;
	YYDEBUG(84, *YYCURSOR);
#line 218 "parse_iso_intervals.re"
	{
		timelib_time *current;

		if (s->have_date || s->have_period) {
			current = s->end;
			s->have_end_date = 1;
		} else {
			current = s->begin;
			s->have_begin_date = 1;
		}
		DEBUG_OUTPUT("datetimebasic | datetimeextended");
		TIMELIB_INIT;
		current->y = timelib_get_nr((char **) &ptr, 4);
		current->m = timelib_get_nr((char **) &ptr, 2);
		current->d = timelib_get_nr((char **) &ptr, 2);
		current->h = timelib_get_nr((char **) &ptr, 2);
		current->i = timelib_get_nr((char **) &ptr, 2);
		current->s = timelib_get_nr((char **) &ptr, 2);
		s->have_date = 1;
		TIMELIB_DEINIT;
		return TIMELIB_ISO_DATE;
	}
#line 834 "<stdout>"
yy85:
	YYDEBUG(85, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '0') goto yy86;
	if (yych <= '2') goto yy87;
	if (yych <= '3') goto yy88;
	goto yy13;
yy86:
	YYDEBUG(86, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '0') goto yy13;
	if (yych <= '9') goto yy89;
	goto yy13;
yy87:
	YYDEBUG(87, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '9') goto yy89;
	goto yy13;
yy88:
	YYDEBUG(88, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych >= '2') goto yy13;
yy89:
	YYDEBUG(89, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych != 'T') goto yy13;
	YYDEBUG(90, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '1') goto yy91;
	if (yych <= '2') goto yy92;
	goto yy13;
yy91:
	YYDEBUG(91, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '9') goto yy93;
	goto yy13;
yy92:
	YYDEBUG(92, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych >= '5') goto yy13;
yy93:
	YYDEBUG(93, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych >= '6') goto yy13;
	YYDEBUG(94, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych >= ':') goto yy13;
	YYDEBUG(95, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych >= '6') goto yy13;
	YYDEBUG(96, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych >= ':') goto yy13;
	YYDEBUG(97, *YYCURSOR);
	yych = *++YYCURSOR;
	if (yych == 'Z') goto yy83;
	goto yy13;
yy98:
	YYDEBUG(98, *YYCURSOR);
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	YYDEBUG(99, *YYCURSOR);
	if (yych <= '/') goto yy100;
	if (yych <= '9') goto yy98;
yy100:
	YYDEBUG(100, *YYCURSOR);
#line 207 "parse_iso_intervals.re"
	{
		DEBUG_OUTPUT("recurrences");
		TIMELIB_INIT;
		ptr++;
		s->recurrences = timelib_get_unsigned_nr((char **) &ptr, 9);
		TIMELIB_DEINIT;
		s->have_recurrences = 1;
		return TIMELIB_PERIOD;
	}
#line 922 "<stdout>"
}
#line 319 "parse_iso_intervals.re"

}