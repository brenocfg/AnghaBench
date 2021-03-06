#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ jsdisp_t ;

/* Variables and functions */
 int /*<<< orphan*/  jsdisp_free (TYPE_1__*) ; 

__attribute__((used)) static inline void jsdisp_release(jsdisp_t *jsdisp)
{
    if(!--jsdisp->ref)
        jsdisp_free(jsdisp);
}