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
struct source_location {int line; int column; int /*<<< orphan*/  file_name; } ;

/* Variables and functions */
 int COLUMN_MASK ; 
 int LINE_MASK ; 
 int /*<<< orphan*/  pr_err (char*,char const*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void print_source_location(const char *prefix,
				struct source_location *loc)
{
	pr_err("%s %s:%d:%d\n", prefix, loc->file_name,
		loc->line & LINE_MASK, loc->column & COLUMN_MASK);
}