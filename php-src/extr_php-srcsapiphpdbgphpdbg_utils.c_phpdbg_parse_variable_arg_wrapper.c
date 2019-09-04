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
typedef  int /*<<< orphan*/  zval ;
typedef  int (* phpdbg_parse_var_func ) (char*,size_t,char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */

__attribute__((used)) static int phpdbg_parse_variable_arg_wrapper(char *name, size_t len, char *keyname, size_t keylen, HashTable *parent, zval *zv, phpdbg_parse_var_func callback) {
	return callback(name, len, keyname, keylen, parent, zv);
}