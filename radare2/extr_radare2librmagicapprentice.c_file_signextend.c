#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int ut64 ;
struct r_magic {int flag; int type; } ;
typedef  unsigned int int64_t ;
typedef  unsigned int int32_t ;
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ RMagic ;

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
 int R_MAGIC_CHECK ; 
 int UNSIGNED ; 
 int /*<<< orphan*/  file_magwarn (TYPE_1__*,char*,int) ; 

ut64 file_signextend(RMagic *ms, struct r_magic *m, ut64 v) {
	if (!(m->flag & UNSIGNED)) {
		switch (m->type) {
		/*
		 * Do not remove the casts below.  They are
		 * vital.  When later compared with the data,
		 * the sign extension must have happened.
		 */
		case FILE_BYTE:
			v = (char) v;
			break;
		case FILE_SHORT:
		case FILE_BESHORT:
		case FILE_LESHORT:
			v = (short) v;
			break;
		case FILE_DATE:
		case FILE_BEDATE:
		case FILE_LEDATE:
		case FILE_MEDATE:
		case FILE_LDATE:
		case FILE_BELDATE:
		case FILE_LELDATE:
		case FILE_MELDATE:
		case FILE_LONG:
		case FILE_BELONG:
		case FILE_LELONG:
		case FILE_MELONG:
		case FILE_FLOAT:
		case FILE_BEFLOAT:
		case FILE_LEFLOAT:
			v = (int32_t) v;
			break;
		case FILE_QUAD:
		case FILE_BEQUAD:
		case FILE_LEQUAD:
		case FILE_QDATE:
		case FILE_QLDATE:
		case FILE_BEQDATE:
		case FILE_BEQLDATE:
		case FILE_LEQDATE:
		case FILE_LEQLDATE:
		case FILE_DOUBLE:
		case FILE_BEDOUBLE:
		case FILE_LEDOUBLE:
			v = (int64_t) v;
			break;
		case FILE_STRING:
		case FILE_PSTRING:
		case FILE_BESTRING16:
		case FILE_LESTRING16:
		case FILE_REGEX:
		case FILE_SEARCH:
		case FILE_DEFAULT:
			break;
		default:
			if (ms->flags & R_MAGIC_CHECK) {
				file_magwarn (ms, "cannot happen: m->type=%d\n",
					m->type);
			}
			return ~0U;
		}
	}
	return v;
}