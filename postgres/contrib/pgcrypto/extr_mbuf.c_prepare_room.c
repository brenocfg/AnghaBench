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
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_3__ {int /*<<< orphan*/ * data; int /*<<< orphan*/ * read_pos; int /*<<< orphan*/ * data_end; int /*<<< orphan*/ * buf_end; } ;
typedef  TYPE_1__ MBuf ;

/* Variables and functions */
 int STEP ; 
 int /*<<< orphan*/ * px_realloc (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void
prepare_room(MBuf *mbuf, int block_len)
{
	uint8	   *newbuf;
	unsigned	newlen;

	if (mbuf->data_end + block_len <= mbuf->buf_end)
		return;

	newlen = (mbuf->buf_end - mbuf->data)
		+ ((block_len + STEP + STEP - 1) & -STEP);

	newbuf = px_realloc(mbuf->data, newlen);

	mbuf->buf_end = newbuf + newlen;
	mbuf->data_end = newbuf + (mbuf->data_end - mbuf->data);
	mbuf->read_pos = newbuf + (mbuf->read_pos - mbuf->data);
	mbuf->data = newbuf;

	return;
}