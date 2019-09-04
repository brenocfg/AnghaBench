#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int n; TYPE_1__* fields; } ;
typedef  TYPE_2__ vle_t ;
typedef  int ut32 ;
struct TYPE_8__ {int type; int /*<<< orphan*/ * types; } ;
typedef  TYPE_3__ ppc_t ;
struct TYPE_6__ {int value; int /*<<< orphan*/  type; } ;

/* Variables and functions */
#define  E_NONE 143 
#define  F_A 142 
#define  F_CMP 141 
#define  F_DCBF 140 
#define  F_DCBL 139 
#define  F_DCI 138 
#define  F_EVX 137 
#define  F_EXT 136 
#define  F_MFPR 135 
#define  F_MTPR 134 
#define  F_X 133 
#define  F_XER 132 
#define  F_XFX 131 
#define  F_XO 130 
#define  F_XRA 129 
#define  F_X_EI 128 
 int /*<<< orphan*/  TYPE_NONE ; 

__attribute__((used)) static void set_ppc_fields(vle_t * v, const ppc_t* p, ut32 data) {
	if (!v) {
		return;
	}
	switch (p->type) {
		case F_X:
		case F_XO:
		case F_EVX:
		{
			v->n = 0;
			if (p->types[0] != TYPE_NONE) {
				v->fields[0].value = (data & 0x3E00000) >> 21;
				v->fields[0].type = p->types[0];
				v->n++;
			}
			if (p->types[1] != TYPE_NONE) {
				v->fields[1].value = (data & 0x1F0000) >> 16;
				v->fields[1].type = p->types[1];
				v->n++;
			}
			if (p->types[2] != TYPE_NONE) {
				v->fields[2].value = (data & 0xF800) >> 11;
				v->fields[2].type = p->types[2];
				v->n++;
			}
		}
			break;
		case F_X_EI:
		{
			v->n = 1;
			v->fields[0].value = (data & 0x8000) >> 15;
			v->fields[0].type = p->types[0];
		}
			break;
		case F_XRA:
		{
			v->n = 3;
			v->fields[1].value = (data & 0x3E00000) >> 21;
			v->fields[1].type = p->types[0];
			v->fields[0].value = (data & 0x1F0000) >> 16;
			v->fields[0].type = p->types[1];
			v->fields[2].value = (data & 0xF800) >> 11;
			v->fields[2].type = p->types[2];
		}
			break;
		case F_CMP:
		{
			v->n = 3;
			v->fields[0].value = (data & 0x3800000) >> 23;
			v->fields[0].type = p->types[0];
			v->fields[1].value = (data & 0x1F0000) >> 16;
			v->fields[1].type = p->types[1];
			v->fields[2].value = (data & 0xF800) >> 11;
			v->fields[2].type = p->types[2];
		}
			break;
		case F_DCBF:
		{
			v->n = 3;
			v->fields[0].value = (data & 0x0E00000) >> 21;
			v->fields[0].type = p->types[0];
			v->fields[1].value = (data & 0x1F0000) >> 16;
			v->fields[1].type = p->types[1];
			v->fields[2].value = (data & 0xF800) >> 11;
			v->fields[2].type = p->types[2];
		}
			break;
		case F_DCBL:
		{
			v->n = 3;
			v->fields[0].value = (data & 0x1E00000) >> 21;
			v->fields[0].type = p->types[0];
			v->fields[1].value = (data & 0x1F0000) >> 16;
			v->fields[1].type = p->types[1];
			v->fields[2].value = (data & 0xF800) >> 11;
			v->fields[2].type = p->types[2];
		}
			break;
		case F_DCI:
		{
			v->n = 1;
			v->fields[0].value = (data & 0xE00000) >> 21;
			v->fields[0].type = p->types[0];
		}
			break;
		case F_EXT:
		{
			v->n = 2;
			v->fields[0].value = (data & 0x3E00000) >> 21;
			v->fields[0].type = p->types[0];
			v->fields[1].value = (data & 0x1F0000) >> 16;
			v->fields[1].type = p->types[1];
		}
			break;
		case F_A:
		{
			v->n = 4;
			v->fields[0].value = (data & 0x1E00000) >> 21;
			v->fields[0].type = p->types[0];
			v->fields[1].value = (data & 0x1F0000) >> 16;
			v->fields[1].type = p->types[1];
			v->fields[2].value = (data & 0xF800) >> 11;
			v->fields[2].type = p->types[2];
			v->fields[3].value = (data & 0x7C0) >> 6;
			v->fields[3].type = p->types[3];
		}
			break;
		case F_XFX:
		{
			v->n = 1;
			v->fields[0].value = (data & 0x3E00000) >> 21;
			v->fields[0].type = p->types[0];
		}
			break;
		case F_XER:
		{
			v->n = 1;
			v->fields[0].value = (data & 0x3800000) >> 23;
			v->fields[0].type = p->types[0];
		}
			break;
		case F_MFPR:
		{
			v->n = 2;
			v->fields[0].value = (data & 0x1E00000) >> 21;
			v->fields[0].type = p->types[0];
			v->fields[1].value = (data & 0x1FF800) >> 11;
			v->fields[1].type = p->types[1];
			break;
		}
		case F_MTPR:
		{
			v->n = 2;
			//inverted
			v->fields[1].value = (data & 0x1E00000) >> 21;
			v->fields[1].type = p->types[1];
			v->fields[0].value = (data & 0x1FF800) >> 11;
			v->fields[0].type = p->types[0];
		}
			break;
		case E_NONE:
		default:
			v->n = 0;
			break;
	}
}