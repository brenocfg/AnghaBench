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
struct avtab_key {int dummy; } ;
struct avtab_datum {int dummy; } ;
struct avtab {int dummy; } ;

/* Variables and functions */
 int avtab_insert (struct avtab*,struct avtab_key*,struct avtab_datum*) ; 

__attribute__((used)) static int avtab_insertf(struct avtab *a, struct avtab_key *k,
			 struct avtab_datum *d, void *p)
{
	return avtab_insert(a, k, d);
}