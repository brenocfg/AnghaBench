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
struct module {int dummy; } ;
struct gcov_info {scalar_t__ filename; } ;

/* Variables and functions */
 int within_module (unsigned long,struct module*) ; 

bool gcov_info_within_module(struct gcov_info *info, struct module *mod)
{
	return within_module((unsigned long)info->filename, mod);
}