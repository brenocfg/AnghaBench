#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_9__ {int /*<<< orphan*/  res; } ;
typedef  TYPE_1__ php_stream_context ;
struct TYPE_10__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_2__ php_stream ;

/* Variables and functions */
 TYPE_1__* PHP_STREAM_CONTEXT (TYPE_2__*) ; 
 int /*<<< orphan*/  php_file_le_pstream () ; 
 int /*<<< orphan*/  php_file_le_stream () ; 
 int /*<<< orphan*/  php_le_stream_context () ; 
 TYPE_1__* php_stream_context_alloc () ; 
 TYPE_2__* zend_fetch_resource2_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* zend_fetch_resource_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static php_stream_context *decode_context_param(zval *contextresource)
{
	php_stream_context *context = NULL;

	context = zend_fetch_resource_ex(contextresource, NULL, php_le_stream_context());
	if (context == NULL) {
		php_stream *stream;

		stream = zend_fetch_resource2_ex(contextresource, NULL, php_file_le_stream(), php_file_le_pstream());

		if (stream) {
			context = PHP_STREAM_CONTEXT(stream);
			if (context == NULL) {
				/* Only way this happens is if file is opened with NO_DEFAULT_CONTEXT
				   param, but then something is called which requires a context.
				   Don't give them the default one though since they already said they
	 			   didn't want it. */
				context = php_stream_context_alloc();
				stream->ctx = context->res;
			}
		}
	}

	return context;
}