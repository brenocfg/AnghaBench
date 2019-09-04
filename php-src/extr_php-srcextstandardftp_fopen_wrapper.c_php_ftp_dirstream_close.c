#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* abstract; } ;
typedef  TYPE_1__ php_stream ;
struct TYPE_6__ {int /*<<< orphan*/ * datastream; int /*<<< orphan*/ * controlstream; } ;
typedef  TYPE_2__ php_ftp_dirstream_data ;

/* Variables and functions */
 int /*<<< orphan*/  efree (TYPE_2__*) ; 
 int /*<<< orphan*/  php_stream_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int php_ftp_dirstream_close(php_stream *stream, int close_handle)
{
	php_ftp_dirstream_data *data = stream->abstract;

	/* close control connection */
	if (data->controlstream) {
		php_stream_close(data->controlstream);
		data->controlstream = NULL;
	}
	/* close data connection */
	php_stream_close(data->datastream);
	data->datastream = NULL;

	efree(data);
	stream->abstract = NULL;

	return 0;
}