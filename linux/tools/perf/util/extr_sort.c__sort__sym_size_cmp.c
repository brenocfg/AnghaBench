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
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ symbol__size (struct symbol*) ; 

__attribute__((used)) static int64_t _sort__sym_size_cmp(struct symbol *sym_l, struct symbol *sym_r)
{
	int64_t size_l = sym_l != NULL ? symbol__size(sym_l) : 0;
	int64_t size_r = sym_r != NULL ? symbol__size(sym_r) : 0;

	return size_l < size_r ? -1 :
		size_l == size_r ? 0 : 1;
}