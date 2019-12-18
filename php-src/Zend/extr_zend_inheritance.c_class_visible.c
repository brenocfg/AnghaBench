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
struct TYPE_5__ {int filename; } ;
struct TYPE_6__ {TYPE_1__ user; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_2__ info; } ;
typedef  TYPE_3__ zend_class_entry ;
typedef  int zend_bool ;

/* Variables and functions */
 int CG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 int ZEND_COMPILE_IGNORE_INTERNAL_CLASSES ; 
 int ZEND_COMPILE_IGNORE_OTHER_FILES ; 
 scalar_t__ ZEND_INTERNAL_CLASS ; 
 scalar_t__ ZEND_USER_CLASS ; 
 int /*<<< orphan*/  compiled_filename ; 
 int /*<<< orphan*/  compiler_options ; 

__attribute__((used)) static zend_bool class_visible(zend_class_entry *ce) {
	if (ce->type == ZEND_INTERNAL_CLASS) {
		return !(CG(compiler_options) & ZEND_COMPILE_IGNORE_INTERNAL_CLASSES);
	} else {
		ZEND_ASSERT(ce->type == ZEND_USER_CLASS);
		return !(CG(compiler_options) & ZEND_COMPILE_IGNORE_OTHER_FILES)
			|| ce->info.user.filename == CG(compiled_filename);
	}
}