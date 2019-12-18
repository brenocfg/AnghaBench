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
struct sw842_param {void** data2; void** data4; void** data8; } ;

/* Variables and functions */
 void* get_input_data (struct sw842_param*,int,int) ; 

__attribute__((used)) static void get_next_data(struct sw842_param *p)
{
	p->data8[0] = get_input_data(p, 0, 64);
	p->data4[0] = get_input_data(p, 0, 32);
	p->data4[1] = get_input_data(p, 4, 32);
	p->data2[0] = get_input_data(p, 0, 16);
	p->data2[1] = get_input_data(p, 2, 16);
	p->data2[2] = get_input_data(p, 4, 16);
	p->data2[3] = get_input_data(p, 6, 16);
}