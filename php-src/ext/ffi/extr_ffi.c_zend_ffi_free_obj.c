#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_2__ {scalar_t__ tags; scalar_t__ symbols; int /*<<< orphan*/ * lib; scalar_t__ persistent; } ;
typedef  TYPE_1__ zend_ffi ;

/* Variables and functions */
 int /*<<< orphan*/  DL_UNLOAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (scalar_t__) ; 
 int /*<<< orphan*/  zend_hash_destroy (scalar_t__) ; 

__attribute__((used)) static void zend_ffi_free_obj(zend_object *object) /* {{{ */
{
	zend_ffi *ffi = (zend_ffi*)object;

	if (ffi->persistent) {
		return;
	}

	if (ffi->lib) {
		DL_UNLOAD(ffi->lib);
		ffi->lib = NULL;
	}

	if (ffi->symbols) {
		zend_hash_destroy(ffi->symbols);
		efree(ffi->symbols);
	}

	if (ffi->tags) {
		zend_hash_destroy(ffi->tags);
		efree(ffi->tags);
	}
}