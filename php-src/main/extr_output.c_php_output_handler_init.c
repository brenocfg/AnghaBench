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
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {size_t size; int flags; TYPE_1__ buffer; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ php_output_handler ;

/* Variables and functions */
 int /*<<< orphan*/  PHP_OUTPUT_HANDLER_INITBUF_SIZE (size_t) ; 
 TYPE_2__* ecalloc (int,int) ; 
 int /*<<< orphan*/  emalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_copy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline php_output_handler *php_output_handler_init(zend_string *name, size_t chunk_size, int flags)
{
	php_output_handler *handler;

	handler = ecalloc(1, sizeof(php_output_handler));
	handler->name = zend_string_copy(name);
	handler->size = chunk_size;
	handler->flags = flags;
	handler->buffer.size = PHP_OUTPUT_HANDLER_INITBUF_SIZE(chunk_size);
	handler->buffer.data = emalloc(handler->buffer.size);

	return handler;
}