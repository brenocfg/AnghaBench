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
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_2__ {int /*<<< orphan*/ * filename; } ;

/* Variables and functions */
 TYPE_1__* CG (int /*<<< orphan*/ ) ; 
 scalar_t__ ZSTR_LEN (int /*<<< orphan*/ *) ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  active_op_array ; 
 size_t sprintf (char*,char*,...) ; 
 int /*<<< orphan*/ * zend_new_interned_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_string_alloc (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_string *zend_build_runtime_definition_key(zend_string *name, unsigned char *lex_pos) /* {{{ */
{
	zend_string *result;
	char char_pos_buf[32];
	size_t char_pos_len = sprintf(char_pos_buf, "%p", lex_pos);
	zend_string *filename = CG(active_op_array)->filename;

	/* NULL, name length, filename length, last accepting char position length */
	result = zend_string_alloc(1 + ZSTR_LEN(name) + ZSTR_LEN(filename) + char_pos_len, 0);
	sprintf(ZSTR_VAL(result), "%c%s%s%s", '\0', ZSTR_VAL(name), ZSTR_VAL(filename), char_pos_buf);
	return zend_new_interned_string(result);
}