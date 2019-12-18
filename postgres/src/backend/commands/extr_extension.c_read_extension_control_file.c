#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int relocatable; int superuser; int encoding; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ExtensionControlFile ;

/* Variables and functions */
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  parse_extension_control_file (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pstrdup (char const*) ; 

__attribute__((used)) static ExtensionControlFile *
read_extension_control_file(const char *extname)
{
	ExtensionControlFile *control;

	/*
	 * Set up default values.  Pointer fields are initially null.
	 */
	control = (ExtensionControlFile *) palloc0(sizeof(ExtensionControlFile));
	control->name = pstrdup(extname);
	control->relocatable = false;
	control->superuser = true;
	control->encoding = -1;

	/*
	 * Parse the primary control file.
	 */
	parse_extension_control_file(control, NULL);

	return control;
}