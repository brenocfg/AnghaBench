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
struct vc_data {int vc_num; } ;
struct TYPE_3__ {scalar_t__* highsize; } ;
struct TYPE_4__ {TYPE_1__ ht; } ;

/* Variables and functions */
 TYPE_2__** speakup_console ; 

__attribute__((used)) static void reset_highlight_buffers(struct vc_data *vc)
{
	int i;
	int vc_num = vc->vc_num;

	for (i = 0; i < 8; i++)
		speakup_console[vc_num]->ht.highsize[i] = 0;
}