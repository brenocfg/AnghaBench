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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  gdImagePtr ;
struct TYPE_2__ {int /*<<< orphan*/  image; } ;

/* Variables and functions */
 int /*<<< orphan*/  Z_OBJ_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gd_image_ce ; 
 int /*<<< orphan*/  object_init_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* php_gd_exgdimage_from_zobj_p (int /*<<< orphan*/ ) ; 

void php_gd_assign_libgdimageptr_as_extgdimage(zval *val, gdImagePtr image)
{
	object_init_ex(val, gd_image_ce);
	php_gd_exgdimage_from_zobj_p(Z_OBJ_P(val))->image = image;
}