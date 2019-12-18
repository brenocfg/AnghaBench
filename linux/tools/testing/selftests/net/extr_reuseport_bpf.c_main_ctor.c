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
struct rlimit {scalar_t__ rlim_cur; scalar_t__ rlim_max; } ;
struct TYPE_3__ {scalar_t__ rlim_cur; scalar_t__ rlim_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 scalar_t__ RLIM_INFINITY ; 
 int /*<<< orphan*/  getrlimit (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__ rlim_old ; 
 int /*<<< orphan*/  setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 

__attribute__((used)) static  __attribute__((constructor)) void main_ctor(void)
{
	getrlimit(RLIMIT_MEMLOCK, &rlim_old);

	if (rlim_old.rlim_cur != RLIM_INFINITY) {
		struct rlimit rlim_new;

		rlim_new.rlim_cur = rlim_old.rlim_cur + (1UL << 20);
		rlim_new.rlim_max = rlim_old.rlim_max + (1UL << 20);
		setrlimit(RLIMIT_MEMLOCK, &rlim_new);
	}
}