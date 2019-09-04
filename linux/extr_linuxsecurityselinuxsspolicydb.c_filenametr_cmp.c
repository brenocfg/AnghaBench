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
struct hashtab {int dummy; } ;
struct filename_trans {int stype; int ttype; int tclass; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filenametr_cmp(struct hashtab *h, const void *k1, const void *k2)
{
	const struct filename_trans *ft1 = k1;
	const struct filename_trans *ft2 = k2;
	int v;

	v = ft1->stype - ft2->stype;
	if (v)
		return v;

	v = ft1->ttype - ft2->ttype;
	if (v)
		return v;

	v = ft1->tclass - ft2->tclass;
	if (v)
		return v;

	return strcmp(ft1->name, ft2->name);

}