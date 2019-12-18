#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* name; } ;
typedef  TYPE_2__ zend_class_entry ;
typedef  int uint32_t ;
struct TYPE_4__ {char* val; } ;

/* Variables and functions */
 int MAY_BE_ANY ; 
 int MAY_BE_ARRAY ; 
 int MAY_BE_ARRAY_KEY_ANY ; 
 int MAY_BE_ARRAY_KEY_LONG ; 
 int MAY_BE_ARRAY_KEY_STRING ; 
 int MAY_BE_ARRAY_OF_ANY ; 
 int MAY_BE_ARRAY_OF_ARRAY ; 
 int MAY_BE_ARRAY_OF_DOUBLE ; 
 int MAY_BE_ARRAY_OF_FALSE ; 
 int MAY_BE_ARRAY_OF_LONG ; 
 int MAY_BE_ARRAY_OF_NULL ; 
 int MAY_BE_ARRAY_OF_OBJECT ; 
 int MAY_BE_ARRAY_OF_REF ; 
 int MAY_BE_ARRAY_OF_RESOURCE ; 
 int MAY_BE_ARRAY_OF_STRING ; 
 int MAY_BE_ARRAY_OF_TRUE ; 
 int MAY_BE_CLASS ; 
 int MAY_BE_DOUBLE ; 
 int MAY_BE_FALSE ; 
 int MAY_BE_IN_REG ; 
 int MAY_BE_LONG ; 
 int MAY_BE_NULL ; 
 int MAY_BE_OBJECT ; 
 int MAY_BE_RC1 ; 
 int MAY_BE_RCN ; 
 int MAY_BE_REF ; 
 int MAY_BE_RESOURCE ; 
 int MAY_BE_STRING ; 
 int MAY_BE_TRUE ; 
 int MAY_BE_UNDEF ; 
 int ZEND_DUMP_RC_INFERENCE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void zend_dump_type_info(uint32_t info, zend_class_entry *ce, int is_instanceof, uint32_t dump_flags)
{
	int first = 1;

	fprintf(stderr, " [");
	if (info & MAY_BE_UNDEF) {
		if (first) first = 0; else fprintf(stderr, ", ");
		fprintf(stderr, "undef");
	}
	if (info & MAY_BE_REF) {
		if (first) first = 0; else fprintf(stderr, ", ");
		fprintf(stderr, "ref");
	}
	if (dump_flags & ZEND_DUMP_RC_INFERENCE) {
		if (info & MAY_BE_RC1) {
			if (first) first = 0; else fprintf(stderr, ", ");
			fprintf(stderr, "rc1");
		}
		if (info & MAY_BE_RCN) {
			if (first) first = 0; else fprintf(stderr, ", ");
			fprintf(stderr, "rcn");
		}
	}
	if (info & MAY_BE_CLASS) {
		if (first) first = 0; else fprintf(stderr, ", ");
		fprintf(stderr, "class");
		if (ce) {
			if (is_instanceof) {
				fprintf(stderr, " (instanceof %s)", ce->name->val);
			} else {
				fprintf(stderr, " (%s)", ce->name->val);
			}
		}
	} else if ((info & MAY_BE_ANY) == MAY_BE_ANY) {
		if (first) first = 0; else fprintf(stderr, ", ");
		fprintf(stderr, "any");
	} else {
		if (info & MAY_BE_NULL) {
			if (first) first = 0; else fprintf(stderr, ", ");
			fprintf(stderr, "null");
		}
		if ((info & MAY_BE_FALSE) && (info & MAY_BE_TRUE)) {
			if (first) first = 0; else fprintf(stderr, ", ");
			fprintf(stderr, "bool");
		} else if (info & MAY_BE_FALSE) {
			if (first) first = 0; else fprintf(stderr, ", ");
			fprintf(stderr, "false");
		} else if (info & MAY_BE_TRUE) {
			if (first) first = 0; else fprintf(stderr, ", ");
			fprintf(stderr, "true");
		}
		if (info & MAY_BE_LONG) {
			if (first) first = 0; else fprintf(stderr, ", ");
			fprintf(stderr, "long");
		}
		if (info & MAY_BE_DOUBLE) {
			if (first) first = 0; else fprintf(stderr, ", ");
			fprintf(stderr, "double");
		}
		if (info & MAY_BE_STRING) {
			if (first) first = 0; else fprintf(stderr, ", ");
			fprintf(stderr, "string");
		}
		if (info & MAY_BE_ARRAY) {
			if (first) first = 0; else fprintf(stderr, ", ");
			fprintf(stderr, "array");
			if ((info & MAY_BE_ARRAY_KEY_ANY) != 0 &&
			    (info & MAY_BE_ARRAY_KEY_ANY) != MAY_BE_ARRAY_KEY_ANY) {
				int afirst = 1;
				fprintf(stderr, " [");
				if (info & MAY_BE_ARRAY_KEY_LONG) {
					if (afirst) afirst = 0; else fprintf(stderr, ", ");
					fprintf(stderr, "long");
				}
				if (info & MAY_BE_ARRAY_KEY_STRING) {
					if (afirst) afirst = 0; else fprintf(stderr, ", ");
						fprintf(stderr, "string");
					}
				fprintf(stderr, "]");
			}
			if (info & (MAY_BE_ARRAY_OF_ANY|MAY_BE_ARRAY_OF_REF)) {
				int afirst = 1;
				fprintf(stderr, " of [");
				if ((info & MAY_BE_ARRAY_OF_ANY) == MAY_BE_ARRAY_OF_ANY) {
					if (afirst) afirst = 0; else fprintf(stderr, ", ");
					fprintf(stderr, "any");
				} else {
					if (info & MAY_BE_ARRAY_OF_NULL) {
						if (afirst) afirst = 0; else fprintf(stderr, ", ");
						fprintf(stderr, "null");
					}
					if (info & MAY_BE_ARRAY_OF_FALSE) {
						if (afirst) afirst = 0; else fprintf(stderr, ", ");
						fprintf(stderr, "false");
					}
					if (info & MAY_BE_ARRAY_OF_TRUE) {
						if (afirst) afirst = 0; else fprintf(stderr, ", ");
						fprintf(stderr, "true");
					}
					if (info & MAY_BE_ARRAY_OF_LONG) {
						if (afirst) afirst = 0; else fprintf(stderr, ", ");
						fprintf(stderr, "long");
					}
					if (info & MAY_BE_ARRAY_OF_DOUBLE) {
						if (afirst) afirst = 0; else fprintf(stderr, ", ");
						fprintf(stderr, "double");
					}
					if (info & MAY_BE_ARRAY_OF_STRING) {
						if (afirst) afirst = 0; else fprintf(stderr, ", ");
						fprintf(stderr, "string");
					}
					if (info & MAY_BE_ARRAY_OF_ARRAY) {
						if (afirst) afirst = 0; else fprintf(stderr, ", ");
						fprintf(stderr, "array");
					}
					if (info & MAY_BE_ARRAY_OF_OBJECT) {
						if (afirst) afirst = 0; else fprintf(stderr, ", ");
						fprintf(stderr, "object");
					}
					if (info & MAY_BE_ARRAY_OF_RESOURCE) {
						if (afirst) afirst = 0; else fprintf(stderr, ", ");
						fprintf(stderr, "resource");
					}
				}
				if (info & MAY_BE_ARRAY_OF_REF) {
					if (afirst) afirst = 0; else fprintf(stderr, ", ");
					fprintf(stderr, "ref");
				}
				fprintf(stderr, "]");
			}
		}
		if (info & MAY_BE_OBJECT) {
			if (first) first = 0; else fprintf(stderr, ", ");
			fprintf(stderr, "object");
			if (ce) {
				if (is_instanceof) {
					fprintf(stderr, " (instanceof %s)", ce->name->val);
				} else {
					fprintf(stderr, " (%s)", ce->name->val);
				}
			}
		}
		if (info & MAY_BE_RESOURCE) {
			if (first) first = 0; else fprintf(stderr, ", ");
			fprintf(stderr, "resource");
		}
	}
//TODO: this is useful only for JIT???
	if (info & MAY_BE_IN_REG) {
		if (first) first = 0; else fprintf(stderr, ", ");
		fprintf(stderr, "reg");
	}
	fprintf(stderr, "]");
}