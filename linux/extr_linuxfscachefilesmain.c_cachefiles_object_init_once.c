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
struct cachefiles_object {int /*<<< orphan*/  work_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct cachefiles_object*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cachefiles_object_init_once(void *_object)
{
	struct cachefiles_object *object = _object;

	memset(object, 0, sizeof(*object));
	spin_lock_init(&object->work_lock);
}