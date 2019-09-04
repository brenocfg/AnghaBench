#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fscache_object {TYPE_2__* cache; } ;
typedef  enum fscache_obj_ref_trace { ____Placeholder_fscache_obj_ref_trace } fscache_obj_ref_trace ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {scalar_t__ (* grab_object ) (struct fscache_object*,int) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  fscache_n_cop_grab_object ; 
 int /*<<< orphan*/  fscache_stat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscache_stat_d (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct fscache_object*,int) ; 

__attribute__((used)) static int fscache_get_object(struct fscache_object *object,
			      enum fscache_obj_ref_trace why)
{
	int ret;

	fscache_stat(&fscache_n_cop_grab_object);
	ret = object->cache->ops->grab_object(object, why) ? 0 : -EAGAIN;
	fscache_stat_d(&fscache_n_cop_grab_object);
	return ret;
}