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
struct mrp_attr {int /*<<< orphan*/  node; } ;
struct mrp_applicant {int /*<<< orphan*/  mad; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mrp_attr*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mrp_attr_destroy(struct mrp_applicant *app, struct mrp_attr *attr)
{
	rb_erase(&attr->node, &app->mad);
	kfree(attr);
}