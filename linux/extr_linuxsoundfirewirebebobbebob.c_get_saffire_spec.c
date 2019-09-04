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
struct snd_bebob_spec {int dummy; } ;
struct fw_unit {int /*<<< orphan*/  directory; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_MODEL ; 
 scalar_t__ fw_csr_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 struct snd_bebob_spec const saffire_le_spec ; 
 struct snd_bebob_spec const saffire_spec ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static const struct snd_bebob_spec *
get_saffire_spec(struct fw_unit *unit)
{
	char name[24] = {0};

	if (fw_csr_string(unit->directory, CSR_MODEL, name, sizeof(name)) < 0)
		return NULL;

	if (strcmp(name, "SaffireLE") == 0)
		return &saffire_le_spec;
	else
		return &saffire_spec;
}