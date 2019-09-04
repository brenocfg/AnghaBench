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
typedef  scalar_t__ u32 ;
struct ima_template_field {int (* field_init ) (struct ima_event_data*,TYPE_1__*) ;} ;
struct ima_template_entry {int template_data_len; TYPE_1__* template_data; struct ima_template_desc* template_desc; } ;
struct ima_template_desc {int num_fields; struct ima_template_field** fields; } ;
struct ima_field_data {int dummy; } ;
struct ima_event_data {int dummy; } ;
typedef  int /*<<< orphan*/  len ;
struct TYPE_2__ {scalar_t__ len; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  ima_free_template_entry (struct ima_template_entry*) ; 
 struct ima_template_desc* ima_template_desc_current () ; 
 struct ima_template_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int stub1 (struct ima_event_data*,TYPE_1__*) ; 

int ima_alloc_init_template(struct ima_event_data *event_data,
			    struct ima_template_entry **entry)
{
	struct ima_template_desc *template_desc = ima_template_desc_current();
	int i, result = 0;

	*entry = kzalloc(sizeof(**entry) + template_desc->num_fields *
			 sizeof(struct ima_field_data), GFP_NOFS);
	if (!*entry)
		return -ENOMEM;

	(*entry)->template_desc = template_desc;
	for (i = 0; i < template_desc->num_fields; i++) {
		struct ima_template_field *field = template_desc->fields[i];
		u32 len;

		result = field->field_init(event_data,
					   &((*entry)->template_data[i]));
		if (result != 0)
			goto out;

		len = (*entry)->template_data[i].len;
		(*entry)->template_data_len += sizeof(len);
		(*entry)->template_data_len += len;
	}
	return 0;
out:
	ima_free_template_entry(*entry);
	*entry = NULL;
	return result;
}