#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct vc_data {int vc_num; int vc_rows; int vc_cols; int /*<<< orphan*/  vc_size_row; scalar_t__ vc_origin; } ;
struct TYPE_3__ {scalar_t__* bgcount; } ;
struct TYPE_4__ {TYPE_1__ ht; } ;

/* Variables and functions */
 int get_attributes (struct vc_data*,int*) ; 
 TYPE_2__** speakup_console ; 

__attribute__((used)) static int count_highlight_color(struct vc_data *vc)
{
	int i, bg;
	int cc;
	int vc_num = vc->vc_num;
	u16 ch;
	u16 *start = (u16 *)vc->vc_origin;

	for (i = 0; i < 8; i++)
		speakup_console[vc_num]->ht.bgcount[i] = 0;

	for (i = 0; i < vc->vc_rows; i++) {
		u16 *end = start + vc->vc_cols * 2;
		u16 *ptr;

		for (ptr = start; ptr < end; ptr++) {
			ch = get_attributes(vc, ptr);
			bg = (ch & 0x70) >> 4;
			speakup_console[vc_num]->ht.bgcount[bg]++;
		}
		start += vc->vc_size_row;
	}

	cc = 0;
	for (i = 0; i < 8; i++)
		if (speakup_console[vc_num]->ht.bgcount[i] > 0)
			cc++;
	return cc;
}