#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
typedef  int ut64 ;
typedef  int ut32 ;
union VALUETYPE {int l; int q; char* s; float f; double d; int /*<<< orphan*/  h; int /*<<< orphan*/  b; } ;
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_11__ {char* s; } ;
struct r_magic {int type; char reln; int vallen; int str_flags; TYPE_2__ value; } ;
typedef  int st32 ;
struct TYPE_10__ {int rm_len; int offset; scalar_t__ s; } ;
struct TYPE_12__ {int offset; TYPE_1__ search; union VALUETYPE ms_value; } ;
typedef  TYPE_3__ RMagic ;

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
 int REGEX_OFFSET_START ; 
 int /*<<< orphan*/  R_MAGIC_DESC ; 
 int /*<<< orphan*/  check_fmt (TYPE_3__*,struct r_magic*) ; 
 char* file_fmttime (int,int) ; 
 int /*<<< orphan*/  file_magerror (TYPE_3__*,char*,int const) ; 
 int /*<<< orphan*/  file_oomem (TYPE_3__*,int) ; 
 int file_printf (TYPE_3__*,int /*<<< orphan*/ ,...) ; 
 int file_signextend (TYPE_3__*,struct r_magic*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,double) ; 
 size_t strcspn (char*,char*) ; 
 char* strdupn (char const*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static st32 mprint(RMagic *ms, struct r_magic *m) {
	ut64 v;
	float vf;
	double vd;
	ut64 t = 0;
 	char *buf = NULL;
	union VALUETYPE *p = &ms->ms_value;

  	switch (m->type) {
  	case FILE_BYTE:
		v = file_signextend(ms, m, (ut64)p->b);
		switch (check_fmt(ms, m)) {
		case -1:
			return -1;
		case 1:
			buf = malloc (2);
			if (snprintf (buf, 2, "%c", (ut8)v)<0) {
				free (buf);
				return -1;
			}
			if (file_printf (ms, R_MAGIC_DESC, buf) == -1) {
				free (buf);
				return -1;
			}
			break;
		default:
			if (file_printf (ms, R_MAGIC_DESC, (ut8)v) == -1) {
				return -1;
			}
			break;
		}
		t = ms->offset + sizeof(char);
		break;
  	case FILE_SHORT:
  	case FILE_BESHORT:
  	case FILE_LESHORT:
		v = file_signextend (ms, m, (ut64)p->h);
		switch (check_fmt (ms, m)) {
		case -1:
			return -1;
		case 1:
			buf = malloc (32);
			if (snprintf (buf, 32, "%hu", (unsigned short)v) < 0) {
				free (buf);
				return -1;
			}
			if (file_printf(ms, R_MAGIC_DESC, buf) == -1) {
				free (buf);
				return -1;
			}
			break;
		default:
			if (file_printf (ms, R_MAGIC_DESC, (unsigned short)v) == -1) {
				return -1;
			}
			break;
		}
		t = ms->offset + sizeof(short);
		break;
  	case FILE_LONG:
  	case FILE_BELONG:
  	case FILE_LELONG:
  	case FILE_MELONG:
		v = file_signextend(ms, m, (ut64)p->l);
		switch (check_fmt(ms, m)) {
		case -1:
			return -1;
		case 1:
			buf = malloc (32);
			if (snprintf (buf, 32, "%u", (ut32)v) < 0) {
				free (buf);
				return -1;
			}
			if (file_printf(ms, R_MAGIC_DESC, buf) == -1) {
				free (buf);
				return -1;
			}
			break;
		default:
			if (file_printf (ms, R_MAGIC_DESC, (ut32)v) == -1) {
				return -1;
			}
			break;
		}
		t = ms->offset + sizeof(st32);
  		break;
  	case FILE_QUAD:
  	case FILE_BEQUAD:
  	case FILE_LEQUAD:
		v = file_signextend(ms, m, p->q);
		if (file_printf (ms, R_MAGIC_DESC, (ut64)v) == -1) {
			return -1;
		}
		t = ms->offset + sizeof(ut64);
  		break;

  	case FILE_STRING:
  	case FILE_PSTRING:
  	case FILE_BESTRING16:
  	case FILE_LESTRING16:
		if (m->reln == '=' || m->reln == '!') {
			if (file_printf (ms, R_MAGIC_DESC, m->value.s) == -1) {
				return -1;
			}
			t = ms->offset + m->vallen;
		}
		else {
			if (*m->value.s == '\0') {
				p->s[strcspn (p->s, "\n")] = '\0';
			}
			if (file_printf (ms, R_MAGIC_DESC, p->s) == -1) {
				return -1;
			}
			t = ms->offset + strlen (p->s);
			if (m->type == FILE_PSTRING) {
				t++;
			}
		}
		break;
	case FILE_DATE:
	case FILE_BEDATE:
	case FILE_LEDATE:
	case FILE_MEDATE:
		if (file_printf (ms, R_MAGIC_DESC, file_fmttime (p->l, 1)) == -1) {
			return -1;
		}
		t = ms->offset + sizeof(time_t);
		break;
	case FILE_LDATE:
	case FILE_BELDATE:
	case FILE_LELDATE:
	case FILE_MELDATE:
		if (file_printf (ms, R_MAGIC_DESC, file_fmttime (p->l, 0)) == -1) {
			return -1;
		}
		t = ms->offset + sizeof(time_t);
		break;
	case FILE_QDATE:
	case FILE_BEQDATE:
	case FILE_LEQDATE:
		if (file_printf (ms, R_MAGIC_DESC, file_fmttime ((ut32)p->q, 1)) == -1) {
			return -1;
		}
		t = ms->offset + sizeof(ut64);
		break;
	case FILE_QLDATE:
	case FILE_BEQLDATE:
	case FILE_LEQLDATE:
		if (file_printf (ms, R_MAGIC_DESC, file_fmttime ((ut32)p->q, 0)) == -1) {
			return -1;
		}
		t = ms->offset + sizeof(ut64);
		break;
  	case FILE_FLOAT:
  	case FILE_BEFLOAT:
  	case FILE_LEFLOAT:
		vf = p->f;
		switch (check_fmt(ms, m)) {
		case -1:
			return -1;
		case 1:
			buf = malloc (32);
			if (snprintf (buf, 32, "%g", vf) < 0) {
				free (buf);
				return -1;
			}
			if (file_printf (ms, R_MAGIC_DESC, buf) == -1) {
				free (buf);
				return -1;
			}
			break;
		default:
			if (file_printf (ms, R_MAGIC_DESC, vf) == -1) {
				return -1;
			}
			break;
		}
		t = ms->offset + sizeof(float);
  		break;
  	case FILE_DOUBLE:
  	case FILE_BEDOUBLE:
  	case FILE_LEDOUBLE:
		vd = p->d;
		switch (check_fmt(ms, m)) {
		case -1:
			return -1;
		case 1:
			buf = malloc (32);
			if (snprintf (buf, 32, "%g", vd) < 0) {
				free (buf);
				return -1;
			}
			if (file_printf (ms, R_MAGIC_DESC, buf) == -1) {
				free (buf);
				return -1;
			}
			break;
		default:
			if (file_printf (ms, R_MAGIC_DESC, vd) == -1) {
				return -1;
			}
			break;
		}
		t = ms->offset + sizeof(double);
  		break;
	case FILE_REGEX: {
		char *cp;
		int rval;

		cp = strdupn((const char *)ms->search.s, ms->search.rm_len);
		if (!cp) {
			file_oomem(ms, ms->search.rm_len);
			return -1;
		}
		rval = file_printf(ms, R_MAGIC_DESC, cp);
		free(cp);

		if (rval == -1) {
			return -1;
		}

		if ((m->str_flags & REGEX_OFFSET_START)) {
			t = ms->search.offset;
		} else {
			t = ms->search.offset + ms->search.rm_len;
		}
		break;
	}

	case FILE_SEARCH:
		if (file_printf (ms, R_MAGIC_DESC, m->value.s) == -1) {
			return -1;
		}
		if ((m->str_flags & REGEX_OFFSET_START)) {
			t = ms->search.offset;
		} else {
			t = ms->search.offset + m->vallen;
		}
		break;
	case FILE_DEFAULT:
		if (file_printf (ms, R_MAGIC_DESC, m->value.s) == -1) {
			return -1;
		}
		t = ms->offset;
		break;
	default:
		file_magerror(ms, "invalid m->type (%d) in mprint()", m->type);
		return -1;
	}
	free (buf);
	return t;
}