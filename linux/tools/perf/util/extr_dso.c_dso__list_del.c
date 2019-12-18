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
struct TYPE_2__ {int /*<<< orphan*/  open_entry; } ;
struct dso {TYPE_1__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 scalar_t__ dso__data_open_cnt ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dso__list_del(struct dso *dso)
{
	list_del_init(&dso->data.open_entry);
	WARN_ONCE(dso__data_open_cnt <= 0,
		  "DSO data fd counter out of bounds.");
	dso__data_open_cnt--;
}