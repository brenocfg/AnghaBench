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
struct version_info {int dummy; } ;
struct reserve_info {int /*<<< orphan*/  size; int /*<<< orphan*/  address; struct reserve_info* next; } ;
struct data {int dummy; } ;

/* Variables and functions */
 struct data data_append_re (struct data,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct data empty_data ; 
 int reservenum ; 

__attribute__((used)) static struct data flatten_reserve_list(struct reserve_info *reservelist,
				 struct version_info *vi)
{
	struct reserve_info *re;
	struct data d = empty_data;
	int    j;

	for (re = reservelist; re; re = re->next) {
		d = data_append_re(d, re->address, re->size);
	}
	/*
	 * Add additional reserved slots if the user asked for them.
	 */
	for (j = 0; j < reservenum; j++) {
		d = data_append_re(d, 0, 0);
	}

	return d;
}