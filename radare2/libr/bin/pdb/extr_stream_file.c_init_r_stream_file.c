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
struct TYPE_3__ {int* pages; int pages_amount; int page_size; int end; scalar_t__ pos; int /*<<< orphan*/ * buf; scalar_t__ error; } ;
typedef  TYPE_1__ R_STREAM_FILE ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */

int init_r_stream_file(R_STREAM_FILE *stream_file, RBuffer *buf, int *pages, int pages_amount, int size, int page_size) {
	stream_file->error = 0;
	stream_file->buf = buf;
	stream_file->pages = pages;
	stream_file->pages_amount = pages_amount;
	stream_file->page_size = page_size;
	if (size == -1) {
		stream_file->end = pages_amount * page_size;
	} else {
		stream_file->end = size;
	}
	stream_file->pos = 0;
	return 1;
}