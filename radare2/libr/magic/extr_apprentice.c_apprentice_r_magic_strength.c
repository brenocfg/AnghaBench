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
struct r_magic {int type; int vallen; int reln; } ;

/* Variables and functions */
#define  FILE_BEDATE 165 
#define  FILE_BEDOUBLE 164 
#define  FILE_BEFLOAT 163 
#define  FILE_BELDATE 162 
#define  FILE_BELONG 161 
#define  FILE_BEQDATE 160 
#define  FILE_BEQLDATE 159 
#define  FILE_BEQUAD 158 
#define  FILE_BESHORT 157 
#define  FILE_BESTRING16 156 
#define  FILE_BYTE 155 
#define  FILE_DATE 154 
#define  FILE_DEFAULT 153 
#define  FILE_DOUBLE 152 
#define  FILE_FLOAT 151 
#define  FILE_LDATE 150 
#define  FILE_LEDATE 149 
#define  FILE_LEDOUBLE 148 
#define  FILE_LEFLOAT 147 
#define  FILE_LELDATE 146 
#define  FILE_LELONG 145 
#define  FILE_LEQDATE 144 
#define  FILE_LEQLDATE 143 
#define  FILE_LEQUAD 142 
#define  FILE_LESHORT 141 
#define  FILE_LESTRING16 140 
#define  FILE_LONG 139 
#define  FILE_MEDATE 138 
#define  FILE_MELDATE 137 
#define  FILE_MELONG 136 
#define  FILE_PSTRING 135 
#define  FILE_QDATE 134 
#define  FILE_QLDATE 133 
#define  FILE_QUAD 132 
#define  FILE_REGEX 131 
#define  FILE_SEARCH 130 
#define  FILE_SHORT 129 
#define  FILE_STRING 128 
 int MULT ; 
 size_t R_MAX (int,int) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  eprintf (char*,int) ; 

__attribute__((used)) static size_t apprentice_r_magic_strength(const struct r_magic *m) {
#define MULT 10
	size_t val = 2 * MULT;	/* baseline strength */

	switch (m->type) {
	case FILE_DEFAULT:	/* make sure this sorts last */
		return 0;
	case FILE_BYTE:
		val += 1 * MULT;
		break;
	case FILE_SHORT:
	case FILE_LESHORT:
	case FILE_BESHORT:
		val += 2 * MULT;
		break;
	case FILE_LONG:
	case FILE_LELONG:
	case FILE_BELONG:
	case FILE_MELONG:
		val += 4 * MULT;
		break;
	case FILE_PSTRING:
	case FILE_STRING:
		val += m->vallen * MULT;
		break;
	case FILE_BESTRING16:
	case FILE_LESTRING16:
		val += m->vallen * MULT / 2;
		break;
	case FILE_SEARCH:
	case FILE_REGEX:
		val += m->vallen * R_MAX (MULT / m->vallen, 1);
		break;
	case FILE_DATE:
	case FILE_LEDATE:
	case FILE_BEDATE:
	case FILE_MEDATE:
	case FILE_LDATE:
	case FILE_LELDATE:
	case FILE_BELDATE:
	case FILE_MELDATE:
	case FILE_FLOAT:
	case FILE_BEFLOAT:
	case FILE_LEFLOAT:
		val += 4 * MULT;
		break;
	case FILE_QUAD:
	case FILE_BEQUAD:
	case FILE_LEQUAD:
	case FILE_QDATE:
	case FILE_LEQDATE:
	case FILE_BEQDATE:
	case FILE_QLDATE:
	case FILE_LEQLDATE:
	case FILE_BEQLDATE:
	case FILE_DOUBLE:
	case FILE_BEDOUBLE:
	case FILE_LEDOUBLE:
		val += 8 * MULT;
		break;
	default:
		eprintf ("Bad type %d\n", m->type);
		abort();
	}

	switch (m->reln) {
	case 'x':	/* matches anything penalize */
	case '!':       /* matches almost anything penalize */
		val = 0;
		break;
	case '=':	/* Exact match, prefer */
		val += MULT;
		break;
	case '>':
	case '<':	/* comparison match reduce strength */
		val -= 2 * MULT;
		break;
	case '^':
	case '&':	/* masking bits, we could count them too */
		val -= MULT;
		break;
	default:
		eprintf ("Bad relation %c\n", m->reln);
		abort();
	}
	return val? val: 1; /* ensure we only return 0 for FILE_DEFAULT */
}