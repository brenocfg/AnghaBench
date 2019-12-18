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
struct variable {scalar_t__ type; scalar_t__ value; } ;
struct descriptor_item {int is_binary; char* data; int /*<<< orphan*/  data_len; } ;
struct ECPGgeneric_varchar {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 scalar_t__ ECPGt_bytea ; 
 int /*<<< orphan*/  ecpg_free (char*) ; 

__attribute__((used)) static void
set_desc_attr(struct descriptor_item *desc_item, struct variable *var,
			  char *tobeinserted)
{
	if (var->type != ECPGt_bytea)
		desc_item->is_binary = false;

	else
	{
		struct ECPGgeneric_varchar *variable =
		(struct ECPGgeneric_varchar *) (var->value);

		desc_item->is_binary = true;
		desc_item->data_len = variable->len;
	}

	ecpg_free(desc_item->data); /* free() takes care of a potential NULL value */
	desc_item->data = (char *) tobeinserted;
}