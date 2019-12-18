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
struct fs_parse_result {int has_value; int negated; int boolean; int /*<<< orphan*/  uint_32; scalar_t__ uint_64; int /*<<< orphan*/  int_32; } ;
struct fs_parameter_spec {int flags; int type; int opt; } ;
struct fs_parameter_enum {int opt; int /*<<< orphan*/  value; int /*<<< orphan*/ * name; } ;
struct fs_parameter_description {int /*<<< orphan*/  name; struct fs_parameter_enum* enums; } ;
struct fs_parameter {char* key; int type; int /*<<< orphan*/  dirfd; int /*<<< orphan*/  string; int /*<<< orphan*/  size; } ;
struct fs_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
 int ENOPARAM ; 
 int /*<<< orphan*/  INT_MAX ; 
#define  __fs_param_wasnt_defined 144 
 int /*<<< orphan*/  bool_names ; 
 struct fs_parameter_spec* fs_lookup_key (struct fs_parameter_description const*,char*) ; 
 int fs_param_deprecated ; 
#define  fs_param_is_blob 143 
#define  fs_param_is_blockdev 142 
#define  fs_param_is_bool 141 
#define  fs_param_is_enum 140 
#define  fs_param_is_fd 139 
#define  fs_param_is_flag 138 
#define  fs_param_is_path 137 
#define  fs_param_is_s32 136 
#define  fs_param_is_string 135 
#define  fs_param_is_u32 134 
#define  fs_param_is_u32_hex 133 
#define  fs_param_is_u32_octal 132 
#define  fs_param_is_u64 131 
 int fs_param_neg_with_no ; 
 int fs_param_v_optional ; 
 int fs_value_is_blob ; 
#define  fs_value_is_file 130 
#define  fs_value_is_flag 129 
#define  fs_value_is_string 128 
 int invalf (struct fs_context*,char*,int /*<<< orphan*/ ,char*) ; 
 int kstrtoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int kstrtouint (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int kstrtoull (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int lookup_constant (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnf (struct fs_context*,char*,int /*<<< orphan*/ ,char*) ; 

int fs_parse(struct fs_context *fc,
	     const struct fs_parameter_description *desc,
	     struct fs_parameter *param,
	     struct fs_parse_result *result)
{
	const struct fs_parameter_spec *p;
	const struct fs_parameter_enum *e;
	int ret = -ENOPARAM, b;

	result->has_value = !!param->string;
	result->negated = false;
	result->uint_64 = 0;

	p = fs_lookup_key(desc, param->key);
	if (!p) {
		/* If we didn't find something that looks like "noxxx", see if
		 * "xxx" takes the "no"-form negative - but only if there
		 * wasn't an value.
		 */
		if (result->has_value)
			goto unknown_parameter;
		if (param->key[0] != 'n' || param->key[1] != 'o' || !param->key[2])
			goto unknown_parameter;

		p = fs_lookup_key(desc, param->key + 2);
		if (!p)
			goto unknown_parameter;
		if (!(p->flags & fs_param_neg_with_no))
			goto unknown_parameter;
		result->boolean = false;
		result->negated = true;
	}

	if (p->flags & fs_param_deprecated)
		warnf(fc, "%s: Deprecated parameter '%s'",
		      desc->name, param->key);

	if (result->negated)
		goto okay;

	/* Certain parameter types only take a string and convert it. */
	switch (p->type) {
	case __fs_param_wasnt_defined:
		return -EINVAL;
	case fs_param_is_u32:
	case fs_param_is_u32_octal:
	case fs_param_is_u32_hex:
	case fs_param_is_s32:
	case fs_param_is_u64:
	case fs_param_is_enum:
	case fs_param_is_string:
		if (param->type != fs_value_is_string)
			goto bad_value;
		if (!result->has_value) {
			if (p->flags & fs_param_v_optional)
				goto okay;
			goto bad_value;
		}
		/* Fall through */
	default:
		break;
	}

	/* Try to turn the type we were given into the type desired by the
	 * parameter and give an error if we can't.
	 */
	switch (p->type) {
	case fs_param_is_flag:
		if (param->type != fs_value_is_flag &&
		    (param->type != fs_value_is_string || result->has_value))
			return invalf(fc, "%s: Unexpected value for '%s'",
				      desc->name, param->key);
		result->boolean = true;
		goto okay;

	case fs_param_is_bool:
		switch (param->type) {
		case fs_value_is_flag:
			result->boolean = true;
			goto okay;
		case fs_value_is_string:
			if (param->size == 0) {
				result->boolean = true;
				goto okay;
			}
			b = lookup_constant(bool_names, param->string, -1);
			if (b == -1)
				goto bad_value;
			result->boolean = b;
			goto okay;
		default:
			goto bad_value;
		}

	case fs_param_is_u32:
		ret = kstrtouint(param->string, 0, &result->uint_32);
		goto maybe_okay;
	case fs_param_is_u32_octal:
		ret = kstrtouint(param->string, 8, &result->uint_32);
		goto maybe_okay;
	case fs_param_is_u32_hex:
		ret = kstrtouint(param->string, 16, &result->uint_32);
		goto maybe_okay;
	case fs_param_is_s32:
		ret = kstrtoint(param->string, 0, &result->int_32);
		goto maybe_okay;
	case fs_param_is_u64:
		ret = kstrtoull(param->string, 0, &result->uint_64);
		goto maybe_okay;

	case fs_param_is_enum:
		for (e = desc->enums; e->name[0]; e++) {
			if (e->opt == p->opt &&
			    strcmp(e->name, param->string) == 0) {
				result->uint_32 = e->value;
				goto okay;
			}
		}
		goto bad_value;

	case fs_param_is_string:
		goto okay;
	case fs_param_is_blob:
		if (param->type != fs_value_is_blob)
			goto bad_value;
		goto okay;

	case fs_param_is_fd: {
		switch (param->type) {
		case fs_value_is_string:
			if (!result->has_value)
				goto bad_value;

			ret = kstrtouint(param->string, 0, &result->uint_32);
			break;
		case fs_value_is_file:
			result->uint_32 = param->dirfd;
			ret = 0;
		default:
			goto bad_value;
		}

		if (result->uint_32 > INT_MAX)
			goto bad_value;
		goto maybe_okay;
	}

	case fs_param_is_blockdev:
	case fs_param_is_path:
		goto okay;
	default:
		BUG();
	}

maybe_okay:
	if (ret < 0)
		goto bad_value;
okay:
	return p->opt;

bad_value:
	return invalf(fc, "%s: Bad value for '%s'", desc->name, param->key);
unknown_parameter:
	return -ENOPARAM;
}