#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_3__ {int /*<<< orphan*/ * image; } ;
typedef  TYPE_1__ php_gd_image_object ;

/* Variables and functions */
 int /*<<< orphan*/  gdImageDestroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* php_gd_exgdimage_from_zobj_p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_object_std_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void php_gd_image_object_free(zend_object *intern)
{
	php_gd_image_object *img_obj_ptr = php_gd_exgdimage_from_zobj_p(intern);
	gdImageDestroy(img_obj_ptr->image);
	img_obj_ptr->image = NULL;

	zend_object_std_dtor(intern);
}