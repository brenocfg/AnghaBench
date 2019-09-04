#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ut16 ;
struct TYPE_8__ {int a_type; int b_type; int a; int b; } ;
struct TYPE_7__ {int opcode; int a_type; int a; } ;
struct TYPE_6__ {int opcode; } ;
struct TYPE_9__ {TYPE_3__ b; TYPE_2__ n; TYPE_1__ code; } ;
typedef  TYPE_4__ op ;

/* Variables and functions */
 scalar_t__ needWord (int) ; 

__attribute__((used)) static int instrGet(ut16 in, op* o, ut16 a, ut16 b) {
	int ret = 1;
	o->code.opcode = in & 0xF;
	if (!(o->code.opcode = in & 0xF)) {
		/* Non basic op code */
		o->n.opcode = (in >> 4) & 0x3F;
		o->n.a_type = (in >> 10) & 0x3F;

		if (needWord(o->n.a_type)) {
			o->n.a = a;
			ret++;
		}
	} else {
		o->b.a_type = (in >> 4) & 0x3F;
		o->b.b_type = (in >> 10) & 0x3F;
		if (needWord(o->b.a_type)) {
			o->b.a = a;
			ret++;
			if (needWord (o->b.b_type)) {
				o->b.b = b;
				ret++;
			}
		} else if (needWord(o->b.b_type)) {
			o->b.b = a;
			ret++;
		}
	}
	return ret;
}