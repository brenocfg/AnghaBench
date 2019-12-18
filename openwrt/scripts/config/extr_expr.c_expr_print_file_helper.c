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

/* Variables and functions */
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  xfwrite (char const*,int /*<<< orphan*/ ,int,void*) ; 

__attribute__((used)) static void expr_print_file_helper(void *data, struct symbol *sym, const char *str)
{
	xfwrite(str, strlen(str), 1, data);
}