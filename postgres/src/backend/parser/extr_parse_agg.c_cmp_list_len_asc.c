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
typedef  int /*<<< orphan*/  ListCell ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 scalar_t__ lfirst (int /*<<< orphan*/  const*) ; 
 int list_length (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
cmp_list_len_asc(const ListCell *a, const ListCell *b)
{
	int			la = list_length((const List *) lfirst(a));
	int			lb = list_length((const List *) lfirst(b));

	return (la > lb) ? 1 : (la == lb) ? 0 : -1;
}