#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int status; int cache; int (* flush_function ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; int /*<<< orphan*/  (* output_function ) (int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ mbfl_convert_filter ;

/* Variables and functions */
 int /*<<< orphan*/  CK (int /*<<< orphan*/ ) ; 
 int* s_form_sjis_fallback_tbl ; 
 int* s_form_tbl ; 
 int s_form_tbl_len ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 
 int stub3 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mbfl_filt_conv_sjis_mac_flush(mbfl_convert_filter *filter)
{
	int i, c1, s1 = 0;
	if (filter->status == 1 && filter->cache > 0) {
		c1 = filter->cache;
		for (i=0;i<s_form_tbl_len;i++) {
			if (c1 == s_form_tbl[i]) {
				s1 = s_form_sjis_fallback_tbl[i];
				break;
			}
		}
		if (s1 > 0) {
			CK((*filter->output_function)((s1 >> 8) & 0xff, filter->data));
			CK((*filter->output_function)(s1 & 0xff, filter->data));
		}
	}
	filter->cache = 0;
	filter->status = 0;

	if (filter->flush_function != NULL) {
		return (*filter->flush_function)(filter->data);
	}

	return 0;
}