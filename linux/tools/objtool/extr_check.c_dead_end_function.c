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
struct symbol {int dummy; } ;
struct objtool_file {int dummy; } ;

/* Variables and functions */
 int __dead_end_function (struct objtool_file*,struct symbol*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool dead_end_function(struct objtool_file *file, struct symbol *func)
{
	return __dead_end_function(file, func, 0);
}