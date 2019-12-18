#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * uspoof; } ;
typedef  TYPE_1__ Spoofchecker_object ;

/* Variables and functions */
 int /*<<< orphan*/  SPOOFCHECKER_ERROR_P (TYPE_1__*) ; 
 int /*<<< orphan*/  intl_error_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uspoof_close (int /*<<< orphan*/ *) ; 

void spoofchecker_object_destroy(Spoofchecker_object* co)
{
	if (!co) {
		return;
	}

	if (co->uspoof) {
		uspoof_close(co->uspoof);
		co->uspoof = NULL;
	}

	intl_error_reset(SPOOFCHECKER_ERROR_P(co));
}