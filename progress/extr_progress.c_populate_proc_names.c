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

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__* default_proc_names ; 
 scalar_t__* proc_names ; 
 int proc_names_cnt ; 
 scalar_t__* realloc (scalar_t__*,int) ; 

void populate_proc_names() {
    int i;
    for(i = 0 ; default_proc_names[i] ; i++) {
        proc_names_cnt++;
        proc_names = realloc(proc_names, proc_names_cnt * sizeof(char *));
        assert(proc_names != NULL);
        proc_names[proc_names_cnt - 1] = default_proc_names[i];
    }
}