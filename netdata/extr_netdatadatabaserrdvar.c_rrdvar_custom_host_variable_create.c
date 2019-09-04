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
struct TYPE_3__ {int /*<<< orphan*/  rrdvar_root_index; } ;
typedef  int /*<<< orphan*/  RRDVAR ;
typedef  TYPE_1__ RRDHOST ;

/* Variables and functions */
 int /*<<< orphan*/ * rrdvar_custom_variable_create (char*,int /*<<< orphan*/ *,char const*) ; 

RRDVAR *rrdvar_custom_host_variable_create(RRDHOST *host, const char *name) {
    return rrdvar_custom_variable_create("host", &host->rrdvar_root_index, name);
}