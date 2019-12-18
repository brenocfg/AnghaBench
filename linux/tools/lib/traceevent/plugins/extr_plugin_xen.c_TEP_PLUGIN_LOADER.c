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
struct tep_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEP_FUNC_ARG_INT ; 
 int /*<<< orphan*/  TEP_FUNC_ARG_STRING ; 
 int /*<<< orphan*/  TEP_FUNC_ARG_VOID ; 
 int /*<<< orphan*/  process_xen_hypercall_name ; 
 int /*<<< orphan*/  tep_register_print_function (struct tep_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int TEP_PLUGIN_LOADER(struct tep_handle *tep)
{
	tep_register_print_function(tep,
				    process_xen_hypercall_name,
				    TEP_FUNC_ARG_STRING,
				    "xen_hypercall_name",
				    TEP_FUNC_ARG_INT,
				    TEP_FUNC_ARG_VOID);
	return 0;
}