#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct string_list {size_t tag; int /*<<< orphan*/  string; } ;
struct TYPE_2__ {char n; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 
 TYPE_1__* symbol_types ; 

__attribute__((used)) static void print_node(FILE * f, struct string_list *list)
{
	if (symbol_types[list->tag].n) {
		putc(symbol_types[list->tag].n, f);
		putc('#', f);
	}
	fputs(list->string, f);
}