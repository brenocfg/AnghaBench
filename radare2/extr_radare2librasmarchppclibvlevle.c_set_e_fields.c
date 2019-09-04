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
typedef  TYPE_3__ e_vle_t ;
struct TYPE_6__ {int value; int /*<<< orphan*/  type; } ;

/* Variables and functions */
#define  E_BD15 150 
#define  E_BD15b 149 
#define  E_BD15c 148 
#define  E_BD24 147 
#define  E_D 146 
#define  E_D8 145 
#define  E_D8_N 144 
#define  E_I16A 143 
#define  E_I16L 142 
#define  E_I16LS 141 
#define  E_IA16 140 
#define  E_IA16U 139 
#define  E_LI20 138 
#define  E_M 137 
#define  E_NONE 136 
#define  E_SCI8 135 
#define  E_SCI8CR 134 
#define  E_SCI8I 133 
#define  E_X 132 
#define  E_XCR 131 
#define  E_XL 130 
#define  E_XLSP 129 
#define  E_XRA 128 

__attribute__((used)) static void set_e_fields(vle_t * v, const e_vle_t* p, ut32 data) {
	if (!v) {
		return;
	}
	switch (p->type) {
		case E_X:
		{
			v->n = 3;
			v->fields[0].value = (data & 0x3E00000) >> 21;
			v->fields[0].type = p->types[0];
			v->fields[1].value = (data & 0x1F0000) >> 16;
			v->fields[1].type = p->types[1];
			v->fields[2].value = (data & 0xF800) >> 11;
			v->fields[2].type = p->types[2];
		}
			break;
		case E_XRA:
		{
			v->n = 3;
			v->fields[0].value = (data & 0x1F0000) >> 16;
			v->fields[0].type = p->types[0];
			v->fields[1].value = (data & 0x3E00000) >> 21;
			v->fields[1].type = p->types[1];
			v->fields[2].value = (data & 0xF800) >> 11;
			v->fields[2].type = p->types[2];
		}
			break;
		case E_XL:
		{
			v->n = 3;
			v->fields[0].value = (data & 0x3E00000) >> 21;
			v->fields[0].type = p->types[0];
			v->fields[1].value = (data & 0x1F0000) >> 16;
			v->fields[1].type = p->types[1];
			v->fields[2].value = (data & 0xF800) >> 11;
			v->fields[2].type = p->types[2];
		}
			break;
		case E_D:
		{
			v->n = 3;
			v->fields[0].value = (data & 0x3E00000) >> 21;
			v->fields[0].type = p->types[0];
			v->fields[1].value = (data & 0x1F0000) >> 16;
			v->fields[1].type = p->types[1];
			v->fields[2].value = data & 0xFFFF;
			if (v->fields[2].value & 0x8000) {
				v->fields[2].value = 0xFFFF0000 | v->fields[2].value;
			}
			v->fields[2].type = p->types[2];
		}
			break;
		case E_D8:
		{
			v->n = 3;
			v->fields[0].value = (data & 0x3E00000) >> 21;
			v->fields[0].type = p->types[0];
			v->fields[1].value = (data & 0x1F0000) >> 16;
			v->fields[1].type = p->types[1];
			v->fields[2].value = data & 0xFF;
			if (v->fields[2].value & 0x80) {
				v->fields[2].value = 0xFFFFFF00 | v->fields[2].value;
			}
			v->fields[2].type = p->types[2];
		}
			break;
		case E_D8_N:
		{
			v->n = 2;
			v->fields[0].value = (data & 0x1F0000) >> 16;
			v->fields[0].type = p->types[0];
			v->fields[1].value = data & 0xFF;
			if (v->fields[1].value & 0x80) {
				v->fields[1].value = 0xFFFFFF00 | v->fields[1].value;
			}
			v->fields[1].type = p->types[1];
		}
			break;
		case E_IA16U:
		{
			v->n = 2;
			v->fields[1].value = (data & 0x3E00000) >> 10;
			v->fields[1].type = p->types[0];
			v->fields[0].value = (data & 0x1F0000) >> 16;
			v->fields[0].type = p->types[1];
			v->fields[1].value |= (data & 0x7FF);
		}
			break;
		case E_IA16:
		case E_I16A:
		{
			v->n = 2;
			v->fields[1].value = (data & 0x3E00000) >> 10;
			v->fields[1].type = p->types[0];
			v->fields[0].value = (data & 0x1F0000) >> 16;
			v->fields[0].type = p->types[1];
			v->fields[1].value |= (data & 0x7FF);
			if (v->fields[1].value & 0x8000) {
				v->fields[1].value = 0xFFFF0000 | v->fields[1].value;
			}
		}
			break;
		case E_SCI8:
		case E_SCI8CR:
		{
			v->n = 3;
			v->fields[0].value = (data & 0x3E00000) >> 21;
			v->fields[0].type = p->types[0];
			if (p->type == E_SCI8CR) {
				v->fields[0].value &= 0x3;
			}
			v->fields[1].value = (data & 0x1F0000) >> 16;
			v->fields[1].type = p->types[1];
			ut32 ui8 = data & 0xFF;
			ut32 scl = (data & 0x300) >> 8;
			ut32 f = data & 0x400;
			switch (scl) {
				case 0:
					v->fields[2].value = ui8 | (f ? 0xffffff00 : 0);
					break;
				case 1:
					v->fields[2].value = (ui8 << 8) | (f ? 0xffff00ff : 0);
					break;
				case 2:
					v->fields[2].value = (ui8 << 16) | (f ? 0xff00ffff : 0);
					break;
				default:
					v->fields[2].value = (ui8 << 24) | (f ? 0x00ffffff : 0);
					break;
			}
			v->fields[2].type = p->types[2];
		}
			break;
		case E_SCI8I:
		{
			v->n = 3;
			v->fields[1].value = (data & 0x3E00000) >> 21;
			v->fields[1].type = p->types[0];
			v->fields[0].value = (data & 0x1F0000) >> 16;
			v->fields[0].type = p->types[1];
			ut32 ui8 = data & 0xFF;
			ut32 scl = (data & 0x300) >> 8;
			ut32 f = data & 0x400;
			switch (scl) {
				case 0:
					v->fields[2].value = ui8 | (f ? 0xffffff00 : 0);
					break;
				case 1:
					v->fields[2].value = (ui8 << 8) | (f ? 0xffff00ff : 0);
					break;
				case 2:
					v->fields[2].value = (ui8 << 16) | (f ? 0xff00ffff : 0);
					break;
				default:
					v->fields[2].value = (ui8 << 24) | (f ? 0x00ffffff : 0);
					break;
			}
			v->fields[2].type = p->types[2];
		}
			break;
		case E_I16L:
		{
			v->n = 2;
			v->fields[0].value = (data & 0x3E00000) >> 21;
			v->fields[0].type = p->types[0];
			v->fields[1].value = (data & 0x1F0000) >> 5;
			v->fields[1].value |= (data & 0x7FF);
			v->fields[1].type = p->types[1];
		}
			break;
		case E_I16LS:
		{
			v->n = 2;
			v->fields[0].value = (data & 0x3E00000) >> 21;
			v->fields[0].type = p->types[0];
			v->fields[1].value = (data & 0x1F0000) >> 5;
			v->fields[1].value |= (data & 0x7FF);
			v->fields[1].type = p->types[1];
		}
			break;
		case E_BD24:
		{
			v->n = 1;
			v->fields[0].value = data & 0x3FFFFFE;
			if (v->fields[0].value & 0x1000000) {
				v->fields[0].value |= 0xFE000000;
			}
			v->fields[0].type = p->types[0];
		}
			break;
		case E_BD15:
		{
			v->n = 2;
			v->fields[0].value = (data & 0xC0000) >> 18;
			v->fields[0].type = p->types[0];
			v->fields[1].value = data & 0xFFFE;
			if (v->fields[1].value & 0x8000) {
				v->fields[1].value |= 0xFFFF0000;
			}
			v->fields[1].type = p->types[1];
		}
			break;
		case E_BD15b:
		{
			v->n = 3;
			v->fields[0].value = (data & 0x300000) >> 20;
			v->fields[0].type = p->types[0];
			v->fields[1].value = (data & 0xF0000) >> 16;
			v->fields[1].type = p->types[0];
			v->fields[2].value = data & 0xFFFE;
			if (v->fields[2].value & 0x8000) {
				v->fields[2].value |= 0xFFFF0000;
			}
			v->fields[2].type = p->types[2];
		}
			break;
		case E_BD15c:
		{
			v->n = 1;
			v->fields[0].value = data & 0xFFFE;
			if (v->fields[0].value & 0x8000) {
				v->fields[0].value |= 0xFFFF0000;
			}
			v->fields[0].type = p->types[0];
		}
			break;
		case E_LI20:
		{
			v->n = 2;
			v->fields[0].value = (data & 0x03E00000) >> 21;
			v->fields[0].type = p->types[0];
			v->fields[1].value = ((data & 0x001F0000) >> 5);
			v->fields[1].value |= ((data & 0x7800) << 5);
			v->fields[1].value |= (data & 0x7FF);
			v->fields[1].type = p->types[1];
			if (v->fields[1].value & 0x80000) {
				v->fields[1].value = 0xFFF00000 | v->fields[1].value;
			}
		}
			break;
		case E_M:
		{
			v->n = 5;
			v->fields[1].value = (data & 0x3E00000) >> 21;
			v->fields[1].type = p->types[1];
			v->fields[0].value = (data & 0x1F0000) >> 16;
			v->fields[0].type = p->types[0];
			v->fields[2].value = (data & 0xF800) >> 11;
			v->fields[2].type = p->types[2];
			v->fields[3].value = (data & 0x7C0) >> 6;
			v->fields[3].type = p->types[3];
			v->fields[4].value = (data & 0x3E) >> 1;
			v->fields[4].type = p->types[4];
		}
			break;
		case E_XCR:
		{
			v->n = 3;
			v->fields[0].value = (data & 0x3000000) >> 24;
			v->fields[0].type = p->types[0];
			v->fields[1].value = (data & 0x1F0000) >> 16;
			v->fields[1].type = p->types[1];
			v->fields[2].value = (data & 0xF800) >> 11;
			v->fields[2].type = p->types[2];
		}
			break;
		case E_XLSP:
		{
			v->n = 3;
			v->fields[0].value = (data & 0x3800000) >> 23;
			v->fields[0].type = p->types[0];
			v->fields[1].value = (data & 0x1C0000) >> 18;
			v->fields[1].type = p->types[1];
		}
			break;
		case E_NONE:
		default:
			v->n = 0;
			break;
	}
}