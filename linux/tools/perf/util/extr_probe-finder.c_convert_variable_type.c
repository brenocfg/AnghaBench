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
struct probe_trace_arg_ref {int user_access; struct probe_trace_arg_ref* next; } ;
struct probe_trace_arg {int /*<<< orphan*/ * type; struct probe_trace_arg_ref* ref; } ;
typedef  int /*<<< orphan*/  sbuf ;
typedef  int /*<<< orphan*/  Dwarf_Die ;

/* Variables and functions */
 int BYTES_TO_BITS (int) ; 
 int DW_TAG_array_type ; 
 int DW_TAG_pointer_type ; 
 int E2BIG ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int MAX_BASIC_TYPE_BITS ; 
 int /*<<< orphan*/  PROBE_TYPE_X ; 
 int STRERR_BUFSIZE ; 
 int /*<<< orphan*/  die_compare_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * die_get_real_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ die_is_signed_type (int /*<<< orphan*/ *) ; 
 int dwarf_bitoffset (int /*<<< orphan*/ *) ; 
 int dwarf_bitsize (int /*<<< orphan*/ *) ; 
 int dwarf_bytesize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_diename (int /*<<< orphan*/ *) ; 
 int dwarf_tag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warning (char*,...) ; 
 scalar_t__ probe_type_is_available (int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,char,int,...) ; 
 int /*<<< orphan*/  str_error_r (int,char*,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 void* strdup (char const*) ; 
 struct probe_trace_arg_ref* zalloc (int) ; 

__attribute__((used)) static int convert_variable_type(Dwarf_Die *vr_die,
				 struct probe_trace_arg *tvar,
				 const char *cast, bool user_access)
{
	struct probe_trace_arg_ref **ref_ptr = &tvar->ref;
	Dwarf_Die type;
	char buf[16];
	char sbuf[STRERR_BUFSIZE];
	int bsize, boffs, total;
	int ret;
	char prefix;

	/* TODO: check all types */
	if (cast && strcmp(cast, "string") != 0 && strcmp(cast, "x") != 0 &&
	    strcmp(cast, "s") != 0 && strcmp(cast, "u") != 0) {
		/* Non string type is OK */
		/* and respect signedness/hexadecimal cast */
		tvar->type = strdup(cast);
		return (tvar->type == NULL) ? -ENOMEM : 0;
	}

	bsize = dwarf_bitsize(vr_die);
	if (bsize > 0) {
		/* This is a bitfield */
		boffs = dwarf_bitoffset(vr_die);
		total = dwarf_bytesize(vr_die);
		if (boffs < 0 || total < 0)
			return -ENOENT;
		ret = snprintf(buf, 16, "b%d@%d/%zd", bsize, boffs,
				BYTES_TO_BITS(total));
		goto formatted;
	}

	if (die_get_real_type(vr_die, &type) == NULL) {
		pr_warning("Failed to get a type information of %s.\n",
			   dwarf_diename(vr_die));
		return -ENOENT;
	}

	pr_debug("%s type is %s.\n",
		 dwarf_diename(vr_die), dwarf_diename(&type));

	if (cast && (!strcmp(cast, "string") || !strcmp(cast, "ustring"))) {
		/* String type */
		ret = dwarf_tag(&type);
		if (ret != DW_TAG_pointer_type &&
		    ret != DW_TAG_array_type) {
			pr_warning("Failed to cast into string: "
				   "%s(%s) is not a pointer nor array.\n",
				   dwarf_diename(vr_die), dwarf_diename(&type));
			return -EINVAL;
		}
		if (die_get_real_type(&type, &type) == NULL) {
			pr_warning("Failed to get a type"
				   " information.\n");
			return -ENOENT;
		}
		if (ret == DW_TAG_pointer_type) {
			while (*ref_ptr)
				ref_ptr = &(*ref_ptr)->next;
			/* Add new reference with offset +0 */
			*ref_ptr = zalloc(sizeof(struct probe_trace_arg_ref));
			if (*ref_ptr == NULL) {
				pr_warning("Out of memory error\n");
				return -ENOMEM;
			}
			(*ref_ptr)->user_access = user_access;
		}
		if (!die_compare_name(&type, "char") &&
		    !die_compare_name(&type, "unsigned char")) {
			pr_warning("Failed to cast into string: "
				   "%s is not (unsigned) char *.\n",
				   dwarf_diename(vr_die));
			return -EINVAL;
		}
		tvar->type = strdup(cast);
		return (tvar->type == NULL) ? -ENOMEM : 0;
	}

	if (cast && (strcmp(cast, "u") == 0))
		prefix = 'u';
	else if (cast && (strcmp(cast, "s") == 0))
		prefix = 's';
	else if (cast && (strcmp(cast, "x") == 0) &&
		 probe_type_is_available(PROBE_TYPE_X))
		prefix = 'x';
	else
		prefix = die_is_signed_type(&type) ? 's' :
			 probe_type_is_available(PROBE_TYPE_X) ? 'x' : 'u';

	ret = dwarf_bytesize(&type);
	if (ret <= 0)
		/* No size ... try to use default type */
		return 0;
	ret = BYTES_TO_BITS(ret);

	/* Check the bitwidth */
	if (ret > MAX_BASIC_TYPE_BITS) {
		pr_info("%s exceeds max-bitwidth. Cut down to %d bits.\n",
			dwarf_diename(&type), MAX_BASIC_TYPE_BITS);
		ret = MAX_BASIC_TYPE_BITS;
	}
	ret = snprintf(buf, 16, "%c%d", prefix, ret);

formatted:
	if (ret < 0 || ret >= 16) {
		if (ret >= 16)
			ret = -E2BIG;
		pr_warning("Failed to convert variable type: %s\n",
			   str_error_r(-ret, sbuf, sizeof(sbuf)));
		return ret;
	}
	tvar->type = strdup(buf);
	if (tvar->type == NULL)
		return -ENOMEM;
	return 0;
}