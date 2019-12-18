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
struct ima_template_field {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IMA_TEMPLATE_FIELD_ID_MAX_LEN ; 
 int IMA_TEMPLATE_NUM_FIELDS_MAX ; 
 struct ima_template_field** kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 struct ima_template_field* lookup_template_field (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 char const* strchrnul (char const*,char) ; 
 int template_fmt_size (char const*) ; 

int template_desc_init_fields(const char *template_fmt,
			      const struct ima_template_field ***fields,
			      int *num_fields)
{
	const char *template_fmt_ptr;
	const struct ima_template_field *found_fields[IMA_TEMPLATE_NUM_FIELDS_MAX];
	int template_num_fields;
	int i, len;

	if (num_fields && *num_fields > 0) /* already initialized? */
		return 0;

	template_num_fields = template_fmt_size(template_fmt);

	if (template_num_fields > IMA_TEMPLATE_NUM_FIELDS_MAX) {
		pr_err("format string '%s' contains too many fields\n",
		       template_fmt);
		return -EINVAL;
	}

	for (i = 0, template_fmt_ptr = template_fmt; i < template_num_fields;
	     i++, template_fmt_ptr += len + 1) {
		char tmp_field_id[IMA_TEMPLATE_FIELD_ID_MAX_LEN + 1];

		len = strchrnul(template_fmt_ptr, '|') - template_fmt_ptr;
		if (len == 0 || len > IMA_TEMPLATE_FIELD_ID_MAX_LEN) {
			pr_err("Invalid field with length %d\n", len);
			return -EINVAL;
		}

		memcpy(tmp_field_id, template_fmt_ptr, len);
		tmp_field_id[len] = '\0';
		found_fields[i] = lookup_template_field(tmp_field_id);
		if (!found_fields[i]) {
			pr_err("field '%s' not found\n", tmp_field_id);
			return -ENOENT;
		}
	}

	if (fields && num_fields) {
		*fields = kmalloc_array(i, sizeof(*fields), GFP_KERNEL);
		if (*fields == NULL)
			return -ENOMEM;

		memcpy(*fields, found_fields, i * sizeof(*fields));
		*num_fields = i;
	}

	return 0;
}