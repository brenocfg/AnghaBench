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
struct TYPE_2__ {int type_no; int /*<<< orphan*/  tvplug_no; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_1__* XGI_crt2type ; 
 int XGIfb_crt2type ; 
 int /*<<< orphan*/  XGIfb_tvplug ; 
 int /*<<< orphan*/  pr_info (char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void XGIfb_search_crt2type(const char *name)
{
	int i = 0;

	if (!name)
		return;

	while (XGI_crt2type[i].type_no != -1) {
		if (!strcmp(name, XGI_crt2type[i].name)) {
			XGIfb_crt2type = XGI_crt2type[i].type_no;
			XGIfb_tvplug = XGI_crt2type[i].tvplug_no;
			break;
		}
		i++;
	}
	if (XGIfb_crt2type < 0)
		pr_info("Invalid CRT2 type: %s\n", name);
}