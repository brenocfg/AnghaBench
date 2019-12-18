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
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ zend_module_entry ;
struct TYPE_4__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_2__ Bucket ;

/* Variables and functions */
 scalar_t__ Z_PTR (int /*<<< orphan*/ ) ; 
 int strcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int module_name_cmp(const void *a, const void *b)
{
	Bucket *f = (Bucket *) a;
	Bucket *s = (Bucket *) b;

	return strcasecmp(	((zend_module_entry *)Z_PTR(f->val))->name,
						((zend_module_entry *)Z_PTR(s->val))->name);
}