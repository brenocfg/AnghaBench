#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  omap_entries; } ;
typedef  TYPE_1__ SOmapStream ;
typedef  int /*<<< orphan*/  SOmapEntry ;
typedef  int /*<<< orphan*/  RListIter ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ ) ; 
 scalar_t__ r_list_iter_get (int /*<<< orphan*/ *) ; 
 scalar_t__ r_list_iter_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_list_iterator (int /*<<< orphan*/ ) ; 

void free_omap_stream(void *stream) {
	SOmapStream *omap_stream = (SOmapStream *) stream;
	SOmapEntry *omap_entry = NULL;
	RListIter *it = r_list_iterator (omap_stream->omap_entries);
	while (r_list_iter_next (it)) {
		omap_entry = (SOmapEntry *) r_list_iter_get (it);
		free (omap_entry);
	}
	r_list_free (omap_stream->omap_entries);
}