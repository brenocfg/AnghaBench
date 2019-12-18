#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ssize_t ;
struct TYPE_4__ {scalar_t__ fpos; scalar_t__ fsize; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ php_stream_memory_data ;
struct TYPE_5__ {int eof; scalar_t__ abstract; } ;
typedef  TYPE_2__ php_stream ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static ssize_t php_stream_memory_read(php_stream *stream, char *buf, size_t count)
{
	php_stream_memory_data *ms = (php_stream_memory_data*)stream->abstract;
	assert(ms != NULL);

	if (ms->fpos == ms->fsize) {
		stream->eof = 1;
		count = 0;
	} else {
		if (ms->fpos + count >= ms->fsize) {
			count = ms->fsize - ms->fpos;
		}
		if (count) {
			assert(ms->data!= NULL);
			assert(buf!= NULL);
			memcpy(buf, ms->data+ms->fpos, count);
			ms->fpos += count;
		}
	}
	return count;
}