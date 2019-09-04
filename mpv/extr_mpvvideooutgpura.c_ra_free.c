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
struct ra {TYPE_1__* fns; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* destroy ) (struct ra*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ra*) ; 
 int /*<<< orphan*/  talloc_free (struct ra*) ; 

void ra_free(struct ra **ra)
{
    if (*ra)
        (*ra)->fns->destroy(*ra);
    talloc_free(*ra);
    *ra = NULL;
}