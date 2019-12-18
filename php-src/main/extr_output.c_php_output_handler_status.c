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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_long ;
struct TYPE_4__ {scalar_t__ used; scalar_t__ size; } ;
struct TYPE_5__ {int flags; TYPE_1__ buffer; scalar_t__ size; scalar_t__ level; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ php_output_handler ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_assoc_long (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_assoc_str (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_copy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline zval *php_output_handler_status(php_output_handler *handler, zval *entry)
{
	ZEND_ASSERT(entry != NULL);

	array_init(entry);
	add_assoc_str(entry, "name", zend_string_copy(handler->name));
	add_assoc_long(entry, "type", (zend_long) (handler->flags & 0xf));
	add_assoc_long(entry, "flags", (zend_long) handler->flags);
	add_assoc_long(entry, "level", (zend_long) handler->level);
	add_assoc_long(entry, "chunk_size", (zend_long) handler->size);
	add_assoc_long(entry, "buffer_size", (zend_long) handler->buffer.size);
	add_assoc_long(entry, "buffer_used", (zend_long) handler->buffer.used);

	return entry;
}