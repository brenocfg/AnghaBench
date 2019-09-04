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
struct config_item {int dummy; } ;
struct childless {int showme; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct childless* to_childless (struct config_item*) ; 

__attribute__((used)) static ssize_t childless_showme_show(struct config_item *item, char *page)
{
	struct childless *childless = to_childless(item);
	ssize_t pos;

	pos = sprintf(page, "%d\n", childless->showme);
	childless->showme++;

	return pos;
}