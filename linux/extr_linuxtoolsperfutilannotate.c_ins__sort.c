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
struct ins {int dummy; } ;
struct arch {int nr_instructions; int /*<<< orphan*/  instructions; } ;

/* Variables and functions */
 int /*<<< orphan*/  ins__cmp ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,int const,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ins__sort(struct arch *arch)
{
	const int nmemb = arch->nr_instructions;

	qsort(arch->instructions, nmemb, sizeof(struct ins), ins__cmp);
}