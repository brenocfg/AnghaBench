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
struct nn_pipebase {int dummy; } ;
struct nn_pipe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_pipebase_getopt (struct nn_pipebase*,int,int,void*,size_t*) ; 

void nn_pipe_getopt (struct nn_pipe *self, int level, int option,
    void *optval, size_t *optvallen)
{

    struct nn_pipebase *pipebase;

    pipebase = (struct nn_pipebase*) self;
    nn_pipebase_getopt (pipebase, level, option, optval, optvallen);
}