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
struct TYPE_2__ {int /*<<< orphan*/  sections_hdrs; } ;
typedef  TYPE_1__ SPEStream ;
typedef  int /*<<< orphan*/  SIMAGE_SECTION_HEADER ;
typedef  int /*<<< orphan*/  RListIter ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ ) ; 
 scalar_t__ r_list_iter_get (int /*<<< orphan*/ *) ; 
 scalar_t__ r_list_iter_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_list_iterator (int /*<<< orphan*/ ) ; 

void free_pe_stream(void *stream)
{
	SPEStream *pe_stream = (SPEStream *) stream;
	SIMAGE_SECTION_HEADER *sctn_header = 0;
	RListIter *it = 0;

	it = r_list_iterator (pe_stream->sections_hdrs);
	while (r_list_iter_next (it)) {
		sctn_header = (SIMAGE_SECTION_HEADER *) r_list_iter_get (it);
		free (sctn_header);
	}
	r_list_free (pe_stream->sections_hdrs);
}