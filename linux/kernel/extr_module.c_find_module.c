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

/* Variables and functions */
 struct module* find_module_all (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  module_assert_mutex () ; 
 int /*<<< orphan*/  strlen (char const*) ; 

struct module *find_module(const char *name)
{
	module_assert_mutex();
	return find_module_all(name, strlen(name), false);
}