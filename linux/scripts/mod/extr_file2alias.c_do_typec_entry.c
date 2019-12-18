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

/* Variables and functions */
 int /*<<< orphan*/  ADD (char*,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  DEF_FIELD (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ TYPEC_ANY_MODE ; 
 scalar_t__ mode ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int svid ; 
 int /*<<< orphan*/  typec_device_id ; 

__attribute__((used)) static int do_typec_entry(const char *filename, void *symval, char *alias)
{
	DEF_FIELD(symval, typec_device_id, svid);
	DEF_FIELD(symval, typec_device_id, mode);

	sprintf(alias, "typec:id%04X", svid);
	ADD(alias, "m", mode != TYPEC_ANY_MODE, mode);

	return 1;
}