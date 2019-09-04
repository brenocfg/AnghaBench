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
typedef  int /*<<< orphan*/  R_STREAM_FILE ;

/* Variables and functions */
 int /*<<< orphan*/  stream_file_read (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  stream_file_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int stream_file_tell (int /*<<< orphan*/ *) ; 

void stream_file_get_data(R_STREAM_FILE *stream_file, char *data) {
	int pos = stream_file_tell (stream_file);
	stream_file_seek (stream_file, 0, 0);
	stream_file_read (stream_file, -1, data);
	stream_file_seek (stream_file, pos, 0);
}