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
struct evp_method_data_st {int /*<<< orphan*/  (* destruct_method ) (void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (void*) ; 

__attribute__((used)) static void destruct_evp_method(void *method, void *data)
{
    struct evp_method_data_st *methdata = data;

    methdata->destruct_method(method);
}