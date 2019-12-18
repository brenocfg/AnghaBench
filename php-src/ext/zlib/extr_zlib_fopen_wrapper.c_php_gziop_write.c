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
struct php_gz_stream_data_t {int /*<<< orphan*/  gz_file; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_3__ {scalar_t__ abstract; } ;
typedef  TYPE_1__ php_stream ;

/* Variables and functions */
 int /*<<< orphan*/  gzwrite (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static ssize_t php_gziop_write(php_stream *stream, const char *buf, size_t count)
{
	struct php_gz_stream_data_t *self = (struct php_gz_stream_data_t *) stream->abstract;

	/* XXX this needs to be looped for the case count > UINT_MAX */
	return gzwrite(self->gz_file, (char *) buf, count);
}