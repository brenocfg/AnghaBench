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
typedef  TYPE_1__* XMLRPC_OPTIONS ;
typedef  int /*<<< orphan*/  XMLRPC_CASE ;
struct TYPE_3__ {int /*<<< orphan*/  id_case; } ;

/* Variables and functions */
 TYPE_1__* XMLRPC_GetDefaultOptions () ; 

XMLRPC_CASE XMLRPC_GetDefaultIdCase() {
   XMLRPC_OPTIONS options = XMLRPC_GetDefaultOptions();
   return options->id_case;
}