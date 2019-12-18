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
struct module {int /*<<< orphan*/  dev_table_buf; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  acpi_id ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_FIELD_ADDR (void*,int /*<<< orphan*/ ,char**) ; 
 unsigned long SIZE_pnp_device_id ; 
 int /*<<< orphan*/  buf_printf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  device_id_check (int /*<<< orphan*/ ,char*,unsigned long,unsigned long const,void*) ; 
 char** id ; 
 int /*<<< orphan*/  pnp_device_id ; 
 char toupper (char) ; 

__attribute__((used)) static void do_pnp_device_entry(void *symval, unsigned long size,
				struct module *mod)
{
	const unsigned long id_size = SIZE_pnp_device_id;
	const unsigned int count = (size / id_size)-1;
	unsigned int i;

	device_id_check(mod->name, "pnp", size, id_size, symval);

	for (i = 0; i < count; i++) {
		DEF_FIELD_ADDR(symval + i*id_size, pnp_device_id, id);
		char acpi_id[sizeof(*id)];
		int j;

		buf_printf(&mod->dev_table_buf,
			   "MODULE_ALIAS(\"pnp:d%s*\");\n", *id);

		/* fix broken pnp bus lowercasing */
		for (j = 0; j < sizeof(acpi_id); j++)
			acpi_id[j] = toupper((*id)[j]);
		buf_printf(&mod->dev_table_buf,
			   "MODULE_ALIAS(\"acpi*:%s:*\");\n", acpi_id);
	}
}