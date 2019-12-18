#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ssize_t ;
struct TYPE_9__ {scalar_t__ position; TYPE_4__* body; } ;
typedef  TYPE_2__ php_stream_input_t ;
struct TYPE_10__ {int eof; TYPE_2__* abstract; } ;
typedef  TYPE_3__ php_stream ;
typedef  scalar_t__ int64_t ;
struct TYPE_8__ {int /*<<< orphan*/  head; } ;
struct TYPE_11__ {TYPE_1__ readfilters; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ SG (int /*<<< orphan*/ ) ; 
 size_t php_stream_read (TYPE_4__*,char*,size_t) ; 
 int /*<<< orphan*/  php_stream_seek (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_stream_write (TYPE_4__*,char*,size_t) ; 
 int /*<<< orphan*/  post_read ; 
 int /*<<< orphan*/  read_post_bytes ; 
 size_t sapi_read_post_block (char*,size_t) ; 

__attribute__((used)) static ssize_t php_stream_input_read(php_stream *stream, char *buf, size_t count) /* {{{ */
{
	php_stream_input_t *input = stream->abstract;
	ssize_t read;

	if (!SG(post_read) && SG(read_post_bytes) < (int64_t)(input->position + count)) {
		/* read requested data from SAPI */
		size_t read_bytes = sapi_read_post_block(buf, count);

		if (read_bytes > 0) {
			php_stream_seek(input->body, 0, SEEK_END);
			php_stream_write(input->body, buf, read_bytes);
		}
	}

	if (!input->body->readfilters.head) {
		/* If the input stream contains filters, it's not really seekable. The
			input->position is likely to be wrong for unfiltered data. */
		php_stream_seek(input->body, input->position, SEEK_SET);
	}
	read = php_stream_read(input->body, buf, count);

	if (!read || read == (size_t) -1) {
		stream->eof = 1;
	} else {
		input->position += read;
	}

	return read;
}