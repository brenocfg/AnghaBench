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
struct kernel_symbol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kernel_symbol_name (struct kernel_symbol const*) ; 
 int strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmp_name(const void *va, const void *vb)
{
	const char *a;
	const struct kernel_symbol *b;
	a = va; b = vb;
	return strcmp(a, kernel_symbol_name(b));
}