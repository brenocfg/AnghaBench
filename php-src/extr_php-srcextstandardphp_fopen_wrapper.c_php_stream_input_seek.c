#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_off_t ;
struct TYPE_5__ {TYPE_3__* body; int /*<<< orphan*/  position; } ;
typedef  TYPE_1__ php_stream_input_t ;
struct TYPE_6__ {TYPE_1__* abstract; } ;
typedef  TYPE_2__ php_stream ;
struct TYPE_7__ {int /*<<< orphan*/  position; } ;

/* Variables and functions */
 int php_stream_seek (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int php_stream_input_seek(php_stream *stream, zend_off_t offset, int whence, zend_off_t *newoffset) /* {{{ */
{
	php_stream_input_t *input = stream->abstract;

	if (input->body) {
		int sought = php_stream_seek(input->body, offset, whence);
		*newoffset = input->position = (input->body)->position;
		return sought;
	}

	return -1;
}