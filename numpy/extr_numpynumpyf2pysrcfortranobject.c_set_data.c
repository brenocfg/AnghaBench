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
typedef  scalar_t__ npy_intp ;
struct TYPE_2__ {char* data; } ;

/* Variables and functions */
 TYPE_1__* save_def ; 

__attribute__((used)) static void set_data(char *d,npy_intp *f) {  /* callback from Fortran */
    if (*f)                                  /* In fortran f=allocated(d) */
        save_def->data = d;
    else
        save_def->data = NULL;
    /* printf("set_data: d=%p,f=%d\n",d,*f); */
}