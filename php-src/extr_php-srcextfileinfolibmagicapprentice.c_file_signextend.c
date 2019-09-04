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
typedef  unsigned int uint64_t ;
struct magic_set {int flags; } ;
struct magic {int flag; int type; } ;
typedef  unsigned int int64_t ;
typedef  unsigned int int32_t ;

/* Variables and functions */
#define  FILE_BEDATE 173 
#define  FILE_BEDOUBLE 172 
#define  FILE_BEFLOAT 171 
#define  FILE_BELDATE 170 
#define  FILE_BELONG 169 
#define  FILE_BEQDATE 168 
#define  FILE_BEQLDATE 167 
#define  FILE_BEQUAD 166 
#define  FILE_BEQWDATE 165 
#define  FILE_BESHORT 164 
#define  FILE_BESTRING16 163 
#define  FILE_BYTE 162 
#define  FILE_CLEAR 161 
#define  FILE_DATE 160 
#define  FILE_DEFAULT 159 
#define  FILE_DER 158 
#define  FILE_DOUBLE 157 
#define  FILE_FLOAT 156 
#define  FILE_INDIRECT 155 
#define  FILE_LDATE 154 
#define  FILE_LEDATE 153 
#define  FILE_LEDOUBLE 152 
#define  FILE_LEFLOAT 151 
#define  FILE_LELDATE 150 
#define  FILE_LELONG 149 
#define  FILE_LEQDATE 148 
#define  FILE_LEQLDATE 147 
#define  FILE_LEQUAD 146 
#define  FILE_LEQWDATE 145 
#define  FILE_LESHORT 144 
#define  FILE_LESTRING16 143 
#define  FILE_LONG 142 
#define  FILE_MEDATE 141 
#define  FILE_MELDATE 140 
#define  FILE_MELONG 139 
#define  FILE_NAME 138 
#define  FILE_PSTRING 137 
#define  FILE_QDATE 136 
#define  FILE_QLDATE 135 
#define  FILE_QUAD 134 
#define  FILE_QWDATE 133 
#define  FILE_REGEX 132 
#define  FILE_SEARCH 131 
#define  FILE_SHORT 130 
#define  FILE_STRING 129 
#define  FILE_USE 128 
 int MAGIC_CHECK ; 
 int UNSIGNED ; 
 int /*<<< orphan*/  file_magwarn (struct magic_set*,char*,int) ; 

uint64_t
file_signextend(struct magic_set *ms, struct magic *m, uint64_t v)
{
	if (!(m->flag & UNSIGNED)) {
		switch(m->type) {
		/*
		 * Do not remove the casts below.  They are
		 * vital.  When later compared with the data,
		 * the sign extension must have happened.
		 */
		case FILE_BYTE:
			v = (signed char) v;
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
		case FILE_QWDATE:
		case FILE_BEQDATE:
		case FILE_BEQLDATE:
		case FILE_BEQWDATE:
		case FILE_LEQDATE:
		case FILE_LEQLDATE:
		case FILE_LEQWDATE:
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
		case FILE_INDIRECT:
		case FILE_NAME:
		case FILE_USE:
		case FILE_CLEAR:
		case FILE_DER:
			break;
		default:
			if (ms->flags & MAGIC_CHECK)
			    file_magwarn(ms, "cannot happen: m->type=%d\n",
				    m->type);
			return ~0U;
		}
	}
	return v;
}