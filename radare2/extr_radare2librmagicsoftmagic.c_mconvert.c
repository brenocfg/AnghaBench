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
typedef  int ut64 ;
typedef  int ut32 ;
union VALUETYPE {char* s; short h; int* hs; int l; int* hl; int q; int /*<<< orphan*/ * hq; } ;
struct r_magic {int type; } ;
typedef  void* st32 ;
struct TYPE_4__ {union VALUETYPE ms_value; } ;
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
 int /*<<< orphan*/  cvt_16 (union VALUETYPE*,struct r_magic*) ; 
 int /*<<< orphan*/  cvt_32 (union VALUETYPE*,struct r_magic*) ; 
 int /*<<< orphan*/  cvt_64 (union VALUETYPE*,struct r_magic*) ; 
 int /*<<< orphan*/  cvt_8 (union VALUETYPE*,struct r_magic*) ; 
 int /*<<< orphan*/  cvt_double (union VALUETYPE*,struct r_magic*) ; 
 int /*<<< orphan*/  cvt_float (union VALUETYPE*,struct r_magic*) ; 
 int /*<<< orphan*/  file_magerror (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  r_read_be32 (int*) ; 
 int /*<<< orphan*/  r_read_le32 (int*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int mconvert(RMagic *ms, struct r_magic *m) {
	union VALUETYPE *p = &ms->ms_value;

	switch (m->type) {
	case FILE_BYTE:
		cvt_8(p, m);
		return 1;
	case FILE_SHORT:
		cvt_16(p, m);
		return 1;
	case FILE_LONG:
	case FILE_DATE:
	case FILE_LDATE:
		cvt_32(p, m);
		return 1;
	case FILE_QUAD:
	case FILE_QDATE:
	case FILE_QLDATE:
		cvt_64(p, m);
		return 1;
	case FILE_STRING:
	case FILE_BESTRING16:
	case FILE_LESTRING16: {
		size_t len;

		/* Null terminate and eat *trailing* return */
		p->s[sizeof(p->s) - 1] = '\0';
		len = strlen(p->s);
		if (len-- && p->s[len] == '\n') {
			p->s[len] = '\0';
		}
		return 1;
	}
	case FILE_PSTRING: {
		char *ptr1 = p->s, *ptr2 = ptr1 + 1;
		size_t len = *p->s;
		if (len >= sizeof (p->s)) {
			len = sizeof (p->s) - 1;
		}
		while (len--) {
			*ptr1++ = *ptr2++;
		}
		*ptr1 = '\0';
		len = strlen(p->s);
		if (len-- && p->s[len] == '\n') {
			p->s[len] = '\0';
		}
		return 1;
	}
	case FILE_BESHORT:
		p->h = (short)((p->hs[0]<<8)|(p->hs[1]));
		cvt_16(p, m);
		return 1;
	case FILE_BELONG:
	case FILE_BEDATE:
	case FILE_BELDATE:
		p->l = (st32) r_read_be32 (p->hl);
		cvt_32(p, m);
		return 1;
	case FILE_BEQUAD:
	case FILE_BEQDATE:
	case FILE_BEQLDATE:
		p->q = (ut64)
		    (((ut64)p->hq[0]<<56)|((ut64)p->hq[1]<<48)|
		     ((ut64)p->hq[2]<<40)|((ut64)p->hq[3]<<32)|
		     ((ut64)p->hq[4]<<24)|((ut64)p->hq[5]<<16)|
		     ((ut64)p->hq[6]<<8)|((ut64)p->hq[7]));
		cvt_64(p, m);
		return 1;
	case FILE_LESHORT:
		p->h = (short)((p->hs[1]<<8)|(p->hs[0]));
		cvt_16(p, m);
		return 1;
	case FILE_LELONG:
	case FILE_LEDATE:
	case FILE_LELDATE:
		p->l = (st32) r_read_le32 (p->hl);
		cvt_32(p, m);
		return 1;
	case FILE_LEQUAD:
	case FILE_LEQDATE:
	case FILE_LEQLDATE:
		p->q = (ut64)
		    (((ut64)p->hq[7]<<56)|((ut64)p->hq[6]<<48)|
		     ((ut64)p->hq[5]<<40)|((ut64)p->hq[4]<<32)|
		     ((ut64)p->hq[3]<<24)|((ut64)p->hq[2]<<16)|
		     ((ut64)p->hq[1]<<8)|((ut64)p->hq[0]));
		cvt_64(p, m);
		return 1;
	case FILE_MELONG:
	case FILE_MEDATE:
	case FILE_MELDATE:
		p->l = (st32)
		    ((p->hl[1]<<24)|(p->hl[0]<<16)|(p->hl[3]<<8)|(p->hl[2]));
		cvt_32(p, m);
		return 1;
	case FILE_FLOAT:
		cvt_float(p, m);
		return 1;
	case FILE_BEFLOAT:
		p->l =  ((ut32)p->hl[0]<<24)|((ut32)p->hl[1]<<16)|
			((ut32)p->hl[2]<<8) |((ut32)p->hl[3]);
		cvt_float(p, m);
		return 1;
	case FILE_LEFLOAT:
		p->l =  ((ut32)p->hl[3]<<24)|((ut32)p->hl[2]<<16)|
			((ut32)p->hl[1]<<8) |((ut32)p->hl[0]);
		cvt_float(p, m);
		return 1;
	case FILE_DOUBLE:
		cvt_double(p, m);
		return 1;
	case FILE_BEDOUBLE:
		p->q =  ((ut64)p->hq[0]<<56)|((ut64)p->hq[1]<<48)|
			((ut64)p->hq[2]<<40)|((ut64)p->hq[3]<<32)|
			((ut64)p->hq[4]<<24)|((ut64)p->hq[5]<<16)|
			((ut64)p->hq[6]<<8) |((ut64)p->hq[7]);
		cvt_double(p, m);
		return 1;
	case FILE_LEDOUBLE:
		p->q =  ((ut64)p->hq[7]<<56)|((ut64)p->hq[6]<<48)|
			((ut64)p->hq[5]<<40)|((ut64)p->hq[4]<<32)|
			((ut64)p->hq[3]<<24)|((ut64)p->hq[2]<<16)|
			((ut64)p->hq[1]<<8) |((ut64)p->hq[0]);
		cvt_double(p, m);
		return 1;
	case FILE_REGEX:
	case FILE_SEARCH:
	case FILE_DEFAULT:
		return 1;
	default:
		file_magerror(ms, "invalid type %d in mconvert()", m->type);
		return 0;
	}
}