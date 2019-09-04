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
struct uwb_rc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct uwb_rc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uwb_rc_init (struct uwb_rc*) ; 

struct uwb_rc *uwb_rc_alloc(void)
{
	struct uwb_rc *rc;
	rc = kzalloc(sizeof(*rc), GFP_KERNEL);
	if (rc == NULL)
		return NULL;
	uwb_rc_init(rc);
	return rc;
}