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
typedef  int /*<<< orphan*/  zval ;
struct TYPE_2__ {scalar_t__ symbol; } ;
typedef  TYPE_1__ phpdbg_breaksymbol_t ;

/* Variables and functions */
 char* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (char*) ; 

__attribute__((used)) static void php_phpdbg_destroy_bp_symbol(zval *brake) /* {{{ */
{
	efree((char *) ((phpdbg_breaksymbol_t *) Z_PTR_P(brake))->symbol);
	efree(Z_PTR_P(brake));
}