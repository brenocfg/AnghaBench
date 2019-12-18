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
struct TYPE_3__ {int indx; } ;
typedef  TYPE_1__ SStreamParseFunc ;
typedef  int /*<<< orphan*/  RListIter ;
typedef  int /*<<< orphan*/  RList ;

/* Variables and functions */
 scalar_t__ r_list_iter_get (int /*<<< orphan*/ *) ; 
 scalar_t__ r_list_iter_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_list_iterator (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void find_indx_in_list(RList *l, int index, SStreamParseFunc **res) {
	SStreamParseFunc *stream_parse_func = 0;
	RListIter *it = 0;

	*res = 0;
	it = r_list_iterator (l);
	while (r_list_iter_next (it)) {
		stream_parse_func = (SStreamParseFunc *) r_list_iter_get (it);
		if (index == stream_parse_func->indx) {
			*res = stream_parse_func;
			return;
		}
	}
}