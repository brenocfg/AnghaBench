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
struct TYPE_2__ {int type_no; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_1__* XGI_tvtype ; 
 int XGIfb_tvmode ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void XGIfb_search_tvstd(const char *name)
{
	int i = 0;

	if (!name)
		return;

	while (XGI_tvtype[i].type_no != -1) {
		if (!strcmp(name, XGI_tvtype[i].name)) {
			XGIfb_tvmode = XGI_tvtype[i].type_no;
			break;
		}
		i++;
	}
}