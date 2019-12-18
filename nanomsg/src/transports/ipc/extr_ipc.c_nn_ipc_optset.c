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
struct nn_optset {int /*<<< orphan*/ * vfptr; } ;
struct nn_ipc_optset {int outbuffersz; int inbuffersz; struct nn_optset base; int /*<<< orphan*/ * sec_attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_assert (struct nn_ipc_optset*) ; 
 struct nn_ipc_optset* nn_alloc (int,char*) ; 
 int /*<<< orphan*/  nn_ipc_optset_vfptr ; 

__attribute__((used)) static struct nn_optset *nn_ipc_optset ()
{
    struct nn_ipc_optset *optset;

    optset = nn_alloc (sizeof (struct nn_ipc_optset), "optset (ipc)");
    alloc_assert (optset);
    optset->base.vfptr = &nn_ipc_optset_vfptr;

    /*  Default values for the IPC options */
    optset->sec_attr = NULL;
    optset->outbuffersz = 4096;
    optset->inbuffersz = 4096;

    return &optset->base;   
}