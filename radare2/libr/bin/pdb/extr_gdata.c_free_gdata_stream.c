#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  globals_list; } ;
struct TYPE_5__ {TYPE_2__* name; } ;
struct TYPE_6__ {TYPE_1__ name; } ;
typedef  TYPE_2__ SGlobal ;
typedef  TYPE_3__ SGDATAStream ;
typedef  int /*<<< orphan*/  RListIter ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ ) ; 
 scalar_t__ r_list_iter_get (int /*<<< orphan*/ *) ; 
 scalar_t__ r_list_iter_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_list_iterator (int /*<<< orphan*/ ) ; 

void free_gdata_stream(void *stream) {
	SGDATAStream *data_stream = (SGDATAStream *) stream;
	SGlobal *global = 0;
	RListIter *it = 0;

	it = r_list_iterator(data_stream->globals_list);
	while (r_list_iter_next(it)) {
		global = (SGlobal *) r_list_iter_get(it);
		if (global->name.name) {
			free (global->name.name);
		}
		free (global);
	}
	r_list_free (data_stream->globals_list);
}