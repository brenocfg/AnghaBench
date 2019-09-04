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
struct TYPE_3__ {int pos; scalar_t__ end; } ;
typedef  TYPE_1__ R_STREAM_FILE ;

/* Variables and functions */

void stream_file_seek(R_STREAM_FILE *stream_file, int offset, int whence) {
	switch (whence) {
	case 0:
		stream_file->pos = offset;
		break;
	case 1:
		stream_file->pos += offset;
		break;
	case 2:
		stream_file->pos = stream_file->end + offset;
		break;
	default:
		break;
	}
	if (stream_file->pos < 0) {
		stream_file->pos = 0;
	}
	if (stream_file->pos > stream_file->end) {
		stream_file->pos = stream_file->end;
	}
}