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
struct separator {scalar_t__ separator; scalar_t__ separator_zero; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_separator(struct separator sep, FILE *fout)
{
	if (sep.separator_zero)
		fputc('\000', fout);
	else if (sep.separator)
		fputs(sep.separator, fout);
}