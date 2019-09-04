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
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int SUCCESS ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  phpdbg_notice (char*,char*,char*,int,char*) ; 
 int /*<<< orphan*/  phpdbg_out (char*) ; 
 int /*<<< orphan*/  phpdbg_xml (char*) ; 
 int /*<<< orphan*/  zend_print_zval_r (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int phpdbg_output_ev_variable(char *name, size_t len, char *keyname, size_t keylen, HashTable *parent, zval *zv) /* {{{ */ {
	phpdbg_notice("eval", "variable=\"%.*s\"", "Printing variable %.*s", (int) len, name);
	phpdbg_xml("<eval %r>");
	zend_print_zval_r(zv, 0);
	phpdbg_xml("</eval>");
	phpdbg_out("\n");

	efree(name);
	efree(keyname);

	return SUCCESS;
}