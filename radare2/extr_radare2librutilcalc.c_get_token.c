#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_7__ {int curr_tok; char* string_value; int /*<<< orphan*/  number_value; } ;
typedef  int RNumCalcToken ;
typedef  TYPE_1__ RNumCalc ;
typedef  int /*<<< orphan*/  RNum ;

/* Variables and functions */
 int RNCDEC ; 
 int RNCEND ; 
 int RNCINC ; 
 int RNCNAME ; 
 int RNCNEG ; 
 int RNCNUMBER ; 
 int RNCROL ; 
 int RNCROR ; 
 int RNCSHL ; 
 int RNCSHR ; 
 int R_NUMCALC_STRSZ ; 
 scalar_t__ cin_get (int /*<<< orphan*/ *,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  cin_get_num (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cin_putback (int /*<<< orphan*/ *,TYPE_1__*,char) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ *,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  isalnum (unsigned char) ; 
 scalar_t__ isspace (int /*<<< orphan*/ ) ; 

__attribute__((used)) static RNumCalcToken get_token(RNum *num, RNumCalc *nc) {
	char ch = 0, c = 0;

	do {
		if (!cin_get (num, nc, &ch)) {
			return nc->curr_tok = RNCEND;
		}
	} while (ch != '\n' && isspace ((ut8)ch));

	switch (ch) {
	case 0:
	case ';':
	case '\n':
		return nc->curr_tok = RNCEND;
	case '+':    // added for ++name and name++
		if (cin_get (num, nc, &c) && c == '+') {
			return nc->curr_tok = RNCINC;
		}
		cin_putback (num, nc, c);
		return nc->curr_tok = (RNumCalcToken) ch;
	// negate hack
	case '~':
		if (cin_get (num, nc, &c) && c == '-') {
			return nc->curr_tok = RNCNEG;
		}
		cin_putback (num, nc, c);
		return nc->curr_tok = (RNumCalcToken) ch;
	// negative number
	case '-':
		if (cin_get (num, nc, &c) && c == '-') {
			return nc->curr_tok = RNCDEC;
		}
		cin_putback (num, nc, c);
		return nc->curr_tok = (RNumCalcToken) ch;
	case '<':
		if (cin_get (num, nc, &c) && c == '<') {
			if (cin_get (num, nc, &c) && c == '<') {
				return nc->curr_tok = RNCROL;
			}
			cin_putback (num, nc, c);
			return nc->curr_tok = RNCSHL;
		}
		cin_putback (num, nc, c);
		return nc->curr_tok = RNCEND;
	case '>':
		if (cin_get (num, nc, &c) && c == '>') {
			if (cin_get (num, nc, &c) && c == '>') {
				return nc->curr_tok = RNCROR;
			}
			cin_putback (num, nc, c);
			return nc->curr_tok = RNCSHR;
		}
		cin_putback (num, nc, c);
		return nc->curr_tok = RNCEND;
	case '^':
	case '&':
	case '|':
	case '*':
	case '%':
	case '/':
	case '(':
	case ')':
	case '=':
		return nc->curr_tok = (RNumCalcToken) ch;
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	case '.':
		cin_putback (num, nc, ch);
		if (!cin_get_num (num, nc, &nc->number_value)) {
			error (num, nc, "invalid number conversion");
			return 1;
		}
		return nc->curr_tok = RNCNUMBER;

#define isvalidchar(x) \
	(isalnum(x) || (x)==':' || (x)=='$' || (x)=='.' || (x)=='_' || (x)=='?' || (x)=='\\' \
	|| (x)==' ' || (x)=='[' || (x)==']' || (x)=='}' || (x)=='{' || ((x)>='0'&&(x)<='9'))

	default:
		{
			int i = 0;
#define stringValueAppend(x) { \
	const size_t max = sizeof (nc->string_value) - 1; \
	if (i < max) nc->string_value[i++] = x; \
	else nc->string_value[max] = 0; \
}
			stringValueAppend(ch);
			if (ch == '[') {
				while (cin_get (num, nc, &ch) && ch!=']') {
					if (i > R_NUMCALC_STRSZ - 1) {
						error (num, nc, "string too long");
						return 0;
					}
					stringValueAppend(ch);
				}
				stringValueAppend(ch);
			} else {
				while (cin_get (num, nc, &ch) && isvalidchar ((unsigned char)ch)) {
					if (i >= R_NUMCALC_STRSZ) {
						error (num, nc, "string too long");
						return 0;
					}
					stringValueAppend(ch);
				}
			}
			stringValueAppend(0);
			if (ch!='\'') {
				cin_putback (num, nc, ch);
			}
			return nc->curr_tok = RNCNAME;
		}
	}
}