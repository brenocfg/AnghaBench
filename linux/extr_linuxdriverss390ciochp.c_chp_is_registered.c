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
struct chp_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * chpid_to_chp (struct chp_id) ; 

int chp_is_registered(struct chp_id chpid)
{
	return chpid_to_chp(chpid) != NULL;
}