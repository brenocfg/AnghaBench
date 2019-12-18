#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_2__ {scalar_t__ s; } ;
struct r_magic {int type; int /*<<< orphan*/  flag; int /*<<< orphan*/  vallen; TYPE_1__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINTEST ; 
#define  FILE_BEDATE 166 
#define  FILE_BEDOUBLE 165 
#define  FILE_BEFLOAT 164 
#define  FILE_BELDATE 163 
#define  FILE_BELONG 162 
#define  FILE_BEQDATE 161 
#define  FILE_BEQLDATE 160 
#define  FILE_BEQUAD 159 
#define  FILE_BESHORT 158 
#define  FILE_BESTRING16 157 
#define  FILE_BYTE 156 
#define  FILE_DATE 155 
#define  FILE_DEFAULT 154 
#define  FILE_DOUBLE 153 
#define  FILE_FLOAT 152 
#define  FILE_INVALID 151 
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
 int /*<<< orphan*/  file_looks_utf8 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void set_test_type(struct r_magic *mstart, struct r_magic *m) {
	switch (m->type) {
	case FILE_BYTE:
	case FILE_SHORT:
	case FILE_LONG:
	case FILE_DATE:
	case FILE_BESHORT:
	case FILE_BELONG:
	case FILE_BEDATE:
	case FILE_LESHORT:
	case FILE_LELONG:
	case FILE_LEDATE:
	case FILE_LDATE:
	case FILE_BELDATE:
	case FILE_LELDATE:
	case FILE_MEDATE:
	case FILE_MELDATE:
	case FILE_MELONG:
	case FILE_QUAD:
	case FILE_LEQUAD:
	case FILE_BEQUAD:
	case FILE_QDATE:
	case FILE_LEQDATE:
	case FILE_BEQDATE:
	case FILE_QLDATE:
	case FILE_LEQLDATE:
	case FILE_BEQLDATE:
	case FILE_FLOAT:
	case FILE_BEFLOAT:
	case FILE_LEFLOAT:
	case FILE_DOUBLE:
	case FILE_BEDOUBLE:
	case FILE_LEDOUBLE:
	case FILE_STRING:
	case FILE_PSTRING:
	case FILE_BESTRING16:
	case FILE_LESTRING16:
		/* binary test, set flag */
		mstart->flag |= BINTEST;
		break;
	case FILE_REGEX:
	case FILE_SEARCH:
		/* binary test if pattern is not text */
		if (file_looks_utf8 ((const ut8 *)m->value.s, m->vallen, NULL, NULL) == 0) {
			mstart->flag |= BINTEST;
		}
		break;
	case FILE_DEFAULT:
		/* can't deduce anything; we shouldn't see this at the
		   top level anyway */
		break;
	case FILE_INVALID:
	default:
		/* invalid search type, but no need to complain here */
		break;
	}
}