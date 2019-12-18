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
struct program_param {TYPE_2__* param; } ;
struct TYPE_3__ {size_t num; } ;
struct TYPE_4__ {TYPE_1__ cur_value; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static inline bool validate_param(struct program_param *pp,
				  size_t expected_size)
{
	if (pp->param->cur_value.num != expected_size) {
		blog(LOG_ERROR,
		     "Parameter '%s' set to invalid size %u, "
		     "expected %u",
		     pp->param->name, (unsigned int)pp->param->cur_value.num,
		     (unsigned int)expected_size);
		return false;
	}

	return true;
}