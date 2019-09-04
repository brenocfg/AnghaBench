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
typedef  int uint32_t ;

/* Variables and functions */
#define  ZEND_FETCH_CLASS_AUTO 133 
 int ZEND_FETCH_CLASS_EXCEPTION ; 
#define  ZEND_FETCH_CLASS_INTERFACE 132 
 int ZEND_FETCH_CLASS_MASK ; 
 int ZEND_FETCH_CLASS_NO_AUTOLOAD ; 
#define  ZEND_FETCH_CLASS_PARENT 131 
#define  ZEND_FETCH_CLASS_SELF 130 
 int ZEND_FETCH_CLASS_SILENT ; 
#define  ZEND_FETCH_CLASS_STATIC 129 
#define  ZEND_FETCH_CLASS_TRAIT 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void zend_dump_class_fetch_type(uint32_t fetch_type)
{
	switch (fetch_type & ZEND_FETCH_CLASS_MASK) {
		case ZEND_FETCH_CLASS_SELF:
			fprintf(stderr, " (self)");
			break;
		case ZEND_FETCH_CLASS_PARENT:
			fprintf(stderr, " (parent)");
			break;
		case ZEND_FETCH_CLASS_STATIC:
			fprintf(stderr, " (static)");
			break;
		case ZEND_FETCH_CLASS_AUTO:
			fprintf(stderr, " (auto)");
			break;
		case ZEND_FETCH_CLASS_INTERFACE:
			fprintf(stderr, " (interface)");
			break;
		case ZEND_FETCH_CLASS_TRAIT:
			fprintf(stderr, " (trait)");
			break;
	}
	if (fetch_type & ZEND_FETCH_CLASS_NO_AUTOLOAD) {
			fprintf(stderr, " (no-autolod)");
	}
	if (fetch_type & ZEND_FETCH_CLASS_SILENT) {
			fprintf(stderr, " (silent)");
	}
	if (fetch_type & ZEND_FETCH_CLASS_EXCEPTION) {
			fprintf(stderr, " (exception)");
	}
}