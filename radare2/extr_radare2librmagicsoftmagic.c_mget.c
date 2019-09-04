#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int ut32 ;
union VALUETYPE {int b; int h; int* hs; int l; int* hl; } ;
struct r_magic {int str_range; int flag; int in_offset; int in_op; int in_type; int vallen; int /*<<< orphan*/  type; } ;
typedef  int st32 ;
struct TYPE_8__ {TYPE_1__* li; } ;
struct TYPE_9__ {int offset; int flags; TYPE_2__ c; union VALUETYPE ms_value; } ;
struct TYPE_7__ {int off; } ;
typedef  TYPE_3__ RMagic ;

/* Variables and functions */
#define  FILE_BEDATE 162 
#define  FILE_BEDOUBLE 161 
#define  FILE_BEFLOAT 160 
#define  FILE_BELDATE 159 
#define  FILE_BELONG 158 
#define  FILE_BESHORT 157 
#define  FILE_BYTE 156 
#define  FILE_DATE 155 
#define  FILE_DEFAULT 154 
#define  FILE_DOUBLE 153 
#define  FILE_FLOAT 152 
#define  FILE_LDATE 151 
#define  FILE_LEDATE 150 
#define  FILE_LEDOUBLE 149 
#define  FILE_LEFLOAT 148 
#define  FILE_LELDATE 147 
#define  FILE_LELONG 146 
#define  FILE_LESHORT 145 
#define  FILE_LONG 144 
#define  FILE_MEDATE 143 
#define  FILE_MELDATE 142 
#define  FILE_MELONG 141 
#define  FILE_OPADD 140 
#define  FILE_OPAND 139 
#define  FILE_OPDIVIDE 138 
 int FILE_OPINDIRECT ; 
 int FILE_OPINVERSE ; 
#define  FILE_OPMINUS 137 
#define  FILE_OPMODULO 136 
#define  FILE_OPMULTIPLY 135 
#define  FILE_OPOR 134 
 int FILE_OPS_MASK ; 
#define  FILE_OPXOR 133 
#define  FILE_PSTRING 132 
#define  FILE_REGEX 131 
#define  FILE_SEARCH 130 
#define  FILE_SHORT 129 
#define  FILE_STRING 128 
 int INDIR ; 
 int INDIROFFADD ; 
 int R_MAGIC_DEBUG ; 
 int /*<<< orphan*/  file_mdump (struct r_magic*) ; 
 int mconvert (TYPE_3__*,struct r_magic*) ; 
 int mcopy (TYPE_3__*,union VALUETYPE*,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int,size_t,int) ; 
 int /*<<< orphan*/  mdebug (int,char*,int) ; 

__attribute__((used)) static int mget(RMagic *ms, const ut8 *s, struct r_magic *m, size_t nbytes, unsigned int cont_level) {
	ut32 offset = ms->offset;
	ut32 count = m->str_range;
	union VALUETYPE *p = &ms->ms_value;

	if (mcopy (ms, p, m->type, m->flag & INDIR, s, offset, nbytes, count) == -1) {
		return -1;
	}

	if ((ms->flags & R_MAGIC_DEBUG) != 0) {
		mdebug(offset, (char *)(void *)p, sizeof(union VALUETYPE));
		file_mdump(m);
	}

	if (m->flag & INDIR) {
		int off = m->in_offset;
		if (m->in_op & FILE_OPINDIRECT) {
			const union VALUETYPE *q =
			    ((const void *)(s + offset + off));
			switch (m->in_type) {
			case FILE_BYTE:
				off = q->b;
				break;
			case FILE_SHORT:
				off = q->h;
				break;
			case FILE_BESHORT:
				off = (short)((q->hs[0]<<8)|(q->hs[1]));
				break;
			case FILE_LESHORT:
				off = (short)((q->hs[1]<<8)|(q->hs[0]));
				break;
			case FILE_LONG:
				off = q->l;
				break;
			case FILE_BELONG:
				off = (st32)((q->hl[0]<<24)|(q->hl[1]<<16)| (q->hl[2]<<8)|(q->hl[3]));
				break;
			case FILE_LELONG:
				off = (st32)((q->hl[3]<<24)|(q->hl[2]<<16)| (q->hl[1]<<8)|(q->hl[0]));
				break;
			case FILE_MELONG:
				off = (st32)((q->hl[1]<<24)|(q->hl[0]<<16)| (q->hl[3]<<8)|(q->hl[2]));
				break;
			}
		}
		switch (m->in_type) {
		case FILE_BYTE:
			if (nbytes < (offset + 1)) {
				return 0;
			}
			if (off) {
				switch (m->in_op & FILE_OPS_MASK) {
				case FILE_OPAND: offset = p->b & off; break;
				case FILE_OPOR: offset = p->b | off; break;
				case FILE_OPXOR: offset = p->b ^ off; break;
				case FILE_OPADD: offset = p->b + off; break;
				case FILE_OPMINUS: offset = p->b - off; break;
				case FILE_OPMULTIPLY: offset = p->b * off; break;
				case FILE_OPDIVIDE: offset = p->b / off; break;
				case FILE_OPMODULO: offset = p->b % off; break;
				}
			} else {
				offset = p->b;
			}
			if (m->in_op & FILE_OPINVERSE) {
				offset = ~offset;
			}
			break;
		case FILE_BESHORT:
			if (nbytes < (offset + 2)) {
				return 0;
			}
			if (off) {
				switch (m->in_op & FILE_OPS_MASK) {
				case FILE_OPAND: offset = (short)((p->hs[0]<<8)| (p->hs[1])) & off; break;
				case FILE_OPOR: offset = (short)((p->hs[0]<<8)| (p->hs[1])) | off; break;
				case FILE_OPXOR: offset = (short)((p->hs[0]<<8)| (p->hs[1])) ^ off; break;
				case FILE_OPADD: offset = (short)((p->hs[0]<<8)| (p->hs[1])) + off; break;
				case FILE_OPMINUS: offset = (short)((p->hs[0]<<8)| (p->hs[1])) - off; break;
				case FILE_OPMULTIPLY: offset = (short)((p->hs[0]<<8)| (p->hs[1])) * off; break;
				case FILE_OPDIVIDE: offset = (short)((p->hs[0]<<8)| (p->hs[1])) / off; break;
				case FILE_OPMODULO: offset = (short)((p->hs[0]<<8)| (p->hs[1])) % off; break;
				}
			} else {
				offset = (short)((p->hs[0] << 8) |
						 (p->hs[1]));
			}
			if (m->in_op & FILE_OPINVERSE) {
				offset = ~offset;
			}
			break;
		case FILE_LESHORT:
			if (nbytes < (offset + 2)) {
				return 0;
			}
			if (off) {
				switch (m->in_op & FILE_OPS_MASK) {
				case FILE_OPAND: offset = (short)((p->hs[1]<<8)| (p->hs[0])) & off; break;
				case FILE_OPOR: offset = (short)((p->hs[1]<<8)| (p->hs[0])) | off; break;
				case FILE_OPXOR: offset = (short)((p->hs[1]<<8)| (p->hs[0])) ^ off; break;
				case FILE_OPADD: offset = (short)((p->hs[1]<<8)| (p->hs[0])) + off; break;
				case FILE_OPMINUS: offset = (short)((p->hs[1]<<8)| (p->hs[0])) - off; break;
				case FILE_OPMULTIPLY: offset = (short)((p->hs[1]<<8)| (p->hs[0])) * off; break;
				case FILE_OPDIVIDE: offset = (short)((p->hs[1]<<8)| (p->hs[0])) / off; break;
				case FILE_OPMODULO: offset = (short)((p->hs[1]<<8)| (p->hs[0])) % off; break;
				}
			} else {
				offset = (short)((p->hs[1] << 8) | (p->hs[0]));
			}
			if (m->in_op & FILE_OPINVERSE) {
				offset = ~offset;
			}
			break;
		case FILE_SHORT:
			if (nbytes < (offset + 2)) {
				return 0;
			}
			if (off) {
				switch (m->in_op & FILE_OPS_MASK) {
				case FILE_OPAND: offset = p->h & off; break;
				case FILE_OPOR: offset = p->h | off; break;
				case FILE_OPXOR: offset = p->h ^ off; break;
				case FILE_OPADD: offset = p->h + off; break;
				case FILE_OPMINUS: offset = p->h - off; break;
				case FILE_OPMULTIPLY: offset = p->h * off; break;
				case FILE_OPDIVIDE: offset = p->h / off; break;
				case FILE_OPMODULO: offset = p->h % off; break;
				}
			} else {
				offset = p->h;
			}
			if (m->in_op & FILE_OPINVERSE) {
				offset = ~offset;
			}
			break;
		case FILE_BELONG:
			if (nbytes < (offset + 4)) {
				return 0;
			}
			if (off) {
				switch (m->in_op & FILE_OPS_MASK) {
				case FILE_OPAND:
					offset = (st32)((p->hl[0]<<24)| (p->hl[1]<<16)| (p->hl[2]<<8)| (p->hl[3])) & off;
					break;
				case FILE_OPOR:
					offset = (st32)((p->hl[0]<<24)| (p->hl[1]<<16)| (p->hl[2]<<8)| (p->hl[3])) | off;
					break;
				case FILE_OPXOR:
					offset = (st32)((p->hl[0]<<24)| (p->hl[1]<<16)| (p->hl[2]<<8)| (p->hl[3])) ^ off;
					break;
				case FILE_OPADD:
					offset = (st32)((p->hl[0]<<24)| (p->hl[1]<<16)| (p->hl[2]<<8)| (p->hl[3])) + off;
					break;
				case FILE_OPMINUS:
					offset = (st32)((p->hl[0]<<24)| (p->hl[1]<<16)| (p->hl[2]<<8)| (p->hl[3])) - off;
					break;
				case FILE_OPMULTIPLY:
					offset = (st32)((p->hl[0]<<24)| (p->hl[1]<<16)| (p->hl[2]<<8)| (p->hl[3])) * off;
					break;
				case FILE_OPDIVIDE:
					offset = (st32)((p->hl[0]<<24)| (p->hl[1]<<16)| (p->hl[2]<<8)| (p->hl[3])) / off;
					break;
				case FILE_OPMODULO:
					offset = (st32)((p->hl[0]<<24)| (p->hl[1]<<16)| (p->hl[2]<<8)| (p->hl[3])) % off;
					break;
				}
			} else {
				offset = (st32) ((p->hl[0] << 24) | (p->hl[1] << 16) | (p->hl[2] << 8) | (p->hl[3]));
			}
			if (m->in_op & FILE_OPINVERSE) {
				offset = ~offset;
			}
			break;
		case FILE_LELONG:
			if (nbytes < (offset + 4)) {
				return 0;
			}
			if (off) {
				switch (m->in_op & FILE_OPS_MASK) {
				case FILE_OPAND:
					offset = (st32)((p->hl[3]<<24)| (p->hl[2]<<16)| (p->hl[1]<<8)| (p->hl[0])) & off;
					break;
				case FILE_OPOR:
					offset = (st32)((p->hl[3]<<24)| (p->hl[2]<<16)| (p->hl[1]<<8)| (p->hl[0])) | off;
					break;
				case FILE_OPXOR:
					offset = (st32)((p->hl[3]<<24)| (p->hl[2]<<16)| (p->hl[1]<<8)| (p->hl[0])) ^ off;
					break;
				case FILE_OPADD:
					offset = (st32)((p->hl[3]<<24)| (p->hl[2]<<16)| (p->hl[1]<<8)| (p->hl[0])) + off;
					break;
				case FILE_OPMINUS:
					offset = (st32)((p->hl[3]<<24)| (p->hl[2]<<16)| (p->hl[1]<<8)| (p->hl[0])) - off;
					break;
				case FILE_OPMULTIPLY:
					offset = (st32)((p->hl[3]<<24)| (p->hl[2]<<16)| (p->hl[1]<<8)| (p->hl[0])) * off;
					break;
				case FILE_OPDIVIDE:
					offset = (st32)((p->hl[3]<<24)| (p->hl[2]<<16)| (p->hl[1]<<8)| (p->hl[0])) / off;
					break;
				case FILE_OPMODULO:
					offset = (st32)((p->hl[3]<<24)| (p->hl[2]<<16)| (p->hl[1]<<8)| (p->hl[0])) % off;
					break;
				}
			} else {
				offset = (st32) (((ut32)p->hl[3] << 24) | (p->hl[2] << 16) | (p->hl[1] << 8) | (p->hl[0]));
			}
			if (m->in_op & FILE_OPINVERSE) {
				offset = ~offset;
			}
			break;
		case FILE_MELONG:
			if (nbytes < (offset + 4)) {
				return 0;
			}
			if (off) {
				switch (m->in_op & FILE_OPS_MASK) {
				case FILE_OPAND:
					offset = (st32)((p->hl[1]<<24)| (p->hl[0]<<16)| (p->hl[3]<<8)| (p->hl[2])) & off;
					break;
				case FILE_OPOR:
					offset = (st32)((p->hl[1]<<24)| (p->hl[0]<<16)| (p->hl[3]<<8)| (p->hl[2])) | off;
					break;
				case FILE_OPXOR:
					offset = (st32)((p->hl[1]<<24)| (p->hl[0]<<16)| (p->hl[3]<<8)| (p->hl[2])) ^ off;
					break;
				case FILE_OPADD:
					offset = (st32)((p->hl[1]<<24)| (p->hl[0]<<16)| (p->hl[3]<<8)| (p->hl[2])) + off;
					break;
				case FILE_OPMINUS:
					offset = (st32)((p->hl[1]<<24)| (p->hl[0]<<16)| (p->hl[3]<<8)| (p->hl[2])) - off;
					break;
				case FILE_OPMULTIPLY:
					offset = (st32)((p->hl[1]<<24)| (p->hl[0]<<16)| (p->hl[3]<<8)| (p->hl[2])) * off;
					break;
				case FILE_OPDIVIDE:
					offset = (st32)((p->hl[1]<<24)| (p->hl[0]<<16)| (p->hl[3]<<8)| (p->hl[2])) / off;
					break;
				case FILE_OPMODULO:
					offset = (st32)((p->hl[1]<<24)| (p->hl[0]<<16)| (p->hl[3]<<8)| (p->hl[2])) % off;
					break;
				}
			} else {
				offset = (st32) ((p->hl[1] << 24) | (p->hl[0] << 16) | (p->hl[3] << 8) | (p->hl[2]));
			}
			if (m->in_op & FILE_OPINVERSE) {
				offset = ~offset;
			}
			break;
		case FILE_LONG:
			if (nbytes < (offset + 4)) {
				return 0;
			}
			if (off) {
				switch (m->in_op & FILE_OPS_MASK) {
				case FILE_OPAND: offset = p->l & off; break;
				case FILE_OPOR: offset = p->l | off; break;
				case FILE_OPXOR: offset = p->l ^ off; break;
				case FILE_OPADD: offset = p->l + off; break;
				case FILE_OPMINUS: offset = p->l - off; break;
				case FILE_OPMULTIPLY: offset = p->l * off; break;
				case FILE_OPDIVIDE: offset = p->l / off; break;
				case FILE_OPMODULO: offset = p->l % off; break;
				}
			} else {
				offset = p->l;
			}
			if (m->in_op & FILE_OPINVERSE) {
				offset = ~offset;
			}
			break;
		}

		if (m->flag & INDIROFFADD) {
			offset += ms->c.li[cont_level - 1].off;
		}
		if (mcopy (ms, p, m->type, 0, s, offset, nbytes, count) == -1) {
			return -1;
		}
		ms->offset = offset;

		if ((ms->flags & R_MAGIC_DEBUG) != 0) {
			mdebug (offset, (char *)(void *)p,
			    sizeof (union VALUETYPE));
			file_mdump(m);
		}
	}

	/* Verify we have enough data to match magic type */
	switch (m->type) {
	case FILE_BYTE:
		if (nbytes < (offset + 1)) { /* should alway be true */
			return 0;
		}
		break;
	case FILE_SHORT:
	case FILE_BESHORT:
	case FILE_LESHORT:
		if (nbytes < (offset + 2)) {
			return 0;
		}
		break;
	case FILE_LONG:
	case FILE_BELONG:
	case FILE_LELONG:
	case FILE_MELONG:
	case FILE_DATE:
	case FILE_BEDATE:
	case FILE_LEDATE:
	case FILE_MEDATE:
	case FILE_LDATE:
	case FILE_BELDATE:
	case FILE_LELDATE:
	case FILE_MELDATE:
	case FILE_FLOAT:
	case FILE_BEFLOAT:
	case FILE_LEFLOAT:
		if (nbytes < (offset + 4)) {
			return 0;
		}
		break;
	case FILE_DOUBLE:
	case FILE_BEDOUBLE:
	case FILE_LEDOUBLE:
		if (nbytes < (offset + 8)) {
			return 0;
		}
		break;
	case FILE_STRING:
	case FILE_PSTRING:
	case FILE_SEARCH:
		if (nbytes < (offset + m->vallen)) {
			return 0;
		}
		break;
	case FILE_REGEX:
		if (nbytes < offset) {
			return 0;
		}
		break;
	case FILE_DEFAULT:	/* nothing to check */
	default:
		break;
	}
	return mconvert (ms, m);
}