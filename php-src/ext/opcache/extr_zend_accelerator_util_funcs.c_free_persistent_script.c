#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * pDestructor; } ;
struct TYPE_6__ {scalar_t__ filename; TYPE_3__ class_table; TYPE_3__ function_table; } ;
struct TYPE_7__ {TYPE_1__ script; } ;
typedef  TYPE_2__ zend_persistent_script ;

/* Variables and functions */
 int /*<<< orphan*/  efree (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_hash_destroy (TYPE_3__*) ; 
 int /*<<< orphan*/  zend_string_release_ex (scalar_t__,int /*<<< orphan*/ ) ; 

void free_persistent_script(zend_persistent_script *persistent_script, int destroy_elements)
{
	if (!destroy_elements) {
		persistent_script->script.function_table.pDestructor = NULL;
		persistent_script->script.class_table.pDestructor = NULL;
	}

	zend_hash_destroy(&persistent_script->script.function_table);
	zend_hash_destroy(&persistent_script->script.class_table);

	if (persistent_script->script.filename) {
		zend_string_release_ex(persistent_script->script.filename, 0);
	}

	efree(persistent_script);
}