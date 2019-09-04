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
struct osst_buffer {int sg_segs; int buffer_size; int orig_sg_segs; TYPE_1__* sg; } ;
struct TYPE_2__ {int length; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_page (TYPE_1__*) ; 

__attribute__((used)) static void normalize_buffer(struct osst_buffer *STbuffer)
{
  int i, order, b_size;

	for (i=0; i < STbuffer->sg_segs; i++) {

		for (b_size = PAGE_SIZE, order = 0;
		     b_size < STbuffer->sg[i].length;
		     b_size *= 2, order++);

		__free_pages(sg_page(&STbuffer->sg[i]), order);
		STbuffer->buffer_size -= STbuffer->sg[i].length;
	}
#if DEBUG
	if (debugging && STbuffer->orig_sg_segs < STbuffer->sg_segs)
		printk(OSST_DEB_MSG "osst :D: Buffer at %p normalized to %d bytes (segs %d).\n",
			     STbuffer->b_data, STbuffer->buffer_size, STbuffer->sg_segs);
#endif
	STbuffer->sg_segs = STbuffer->orig_sg_segs = 0;
}