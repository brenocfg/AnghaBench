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
typedef  size_t u_int8_t ;
struct xt_match {size_t family; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  match; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* xt ; 

int xt_register_match(struct xt_match *match)
{
	u_int8_t af = match->family;

	mutex_lock(&xt[af].mutex);
	list_add(&match->list, &xt[af].match);
	mutex_unlock(&xt[af].mutex);
	return 0;
}