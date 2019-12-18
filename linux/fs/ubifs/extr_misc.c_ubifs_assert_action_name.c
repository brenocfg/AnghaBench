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
struct ubifs_info {size_t assert_action; } ;

/* Variables and functions */
 char const** assert_names ; 

const char *ubifs_assert_action_name(struct ubifs_info *c)
{
	return assert_names[c->assert_action];
}