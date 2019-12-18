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
typedef  int /*<<< orphan*/  cap_value_t ;
typedef  int /*<<< orphan*/  cap_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_EFFECTIVE ; 
 int /*<<< orphan*/  CAP_SET ; 
 int /*<<< orphan*/  CAP_SETGID ; 
 int /*<<< orphan*/  CAP_SETUID ; 
 int /*<<< orphan*/  cap_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_get_proc () ; 
 int /*<<< orphan*/  cap_set_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_set_proc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drop_caps(bool setid_retained)
{
	cap_value_t cap_values[] = {CAP_SETUID, CAP_SETGID};
	cap_t caps;

	caps = cap_get_proc();
	if (setid_retained)
		cap_set_flag(caps, CAP_EFFECTIVE, 2, cap_values, CAP_SET);
	else
		cap_clear(caps);
	cap_set_proc(caps);
	cap_free(caps);
}