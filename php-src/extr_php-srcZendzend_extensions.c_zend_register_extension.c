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
typedef  int /*<<< orphan*/  zend_extension ;
typedef  int /*<<< orphan*/  DL_HANDLE ;

/* Variables and functions */
 int SUCCESS ; 

int zend_register_extension(zend_extension *new_extension, DL_HANDLE handle)
{
#if ZEND_EXTENSIONS_SUPPORT
	zend_extension extension;

	extension = *new_extension;
	extension.handle = handle;

	zend_extension_dispatch_message(ZEND_EXTMSG_NEW_EXTENSION, &extension);

	zend_llist_add_element(&zend_extensions, &extension);

	if (extension.op_array_ctor) {
		zend_extension_flags |= ZEND_EXTENSIONS_HAVE_OP_ARRAY_CTOR;
	}
	if (extension.op_array_dtor) {
		zend_extension_flags |= ZEND_EXTENSIONS_HAVE_OP_ARRAY_DTOR;
	}
	if (extension.op_array_handler) {
		zend_extension_flags |= ZEND_EXTENSIONS_HAVE_OP_ARRAY_HANDLER;
	}
	if (extension.op_array_persist_calc) {
		zend_extension_flags |= ZEND_EXTENSIONS_HAVE_OP_ARRAY_PERSIST_CALC;
	}
	if (extension.op_array_persist) {
		zend_extension_flags |= ZEND_EXTENSIONS_HAVE_OP_ARRAY_PERSIST;
	}
	/*fprintf(stderr, "Loaded %s, version %s\n", extension.name, extension.version);*/
#endif

	return SUCCESS;
}