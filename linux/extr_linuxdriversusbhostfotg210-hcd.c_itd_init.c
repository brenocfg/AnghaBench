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
struct fotg210_itd {int* index; int /*<<< orphan*/ * hw_bufp; int /*<<< orphan*/  hw_next; } ;
struct fotg210_iso_stream {int /*<<< orphan*/  buf2; int /*<<< orphan*/  buf1; int /*<<< orphan*/  buf0; } ;
struct fotg210_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FOTG210_LIST_END (struct fotg210_hcd*) ; 

__attribute__((used)) static inline void itd_init(struct fotg210_hcd *fotg210,
		struct fotg210_iso_stream *stream, struct fotg210_itd *itd)
{
	int i;

	/* it's been recently zeroed */
	itd->hw_next = FOTG210_LIST_END(fotg210);
	itd->hw_bufp[0] = stream->buf0;
	itd->hw_bufp[1] = stream->buf1;
	itd->hw_bufp[2] = stream->buf2;

	for (i = 0; i < 8; i++)
		itd->index[i] = -1;

	/* All other fields are filled when scheduling */
}