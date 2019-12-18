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
struct TYPE_2__ {int /*<<< orphan*/  fpo_data_list; } ;
typedef  int /*<<< orphan*/  SFPO_DATA_V2 ;
typedef  TYPE_1__ SFPONewStream ;
typedef  int /*<<< orphan*/  RListIter ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ ) ; 
 scalar_t__ r_list_iter_get (int /*<<< orphan*/ *) ; 
 scalar_t__ r_list_iter_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_list_iterator (int /*<<< orphan*/ ) ; 

void free_fpo_new_stream(void *stream)
{
	SFPONewStream *fpo_stream = (SFPONewStream *) stream;
	RListIter *it = 0;
	SFPO_DATA_V2 *fpo_data = 0;

	it = r_list_iterator(fpo_stream->fpo_data_list);
	while (r_list_iter_next(it)) {
		fpo_data = (SFPO_DATA_V2 *) r_list_iter_get(it);
		free(fpo_data);
	}
	r_list_free (fpo_stream->fpo_data_list);
}