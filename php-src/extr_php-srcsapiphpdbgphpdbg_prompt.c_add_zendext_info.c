#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ zend_extension ;

/* Variables and functions */
 int /*<<< orphan*/  phpdbg_write (char*,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_zendext_info(zend_extension *ext) /* {{{ */ {
	phpdbg_write("extension", "name=\"%s\"", "%s\n", ext->name);
	return 0;
}