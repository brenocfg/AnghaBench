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
struct TYPE_2__ {unsigned int* states; int depth; unsigned int* remainings; } ;
struct CertDecode {TYPE_1__ stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (unsigned int*,unsigned int*,int) ; 

__attribute__((used)) static unsigned
ASN1_pop(struct CertDecode *x)
{
    unsigned next_state;
    next_state = x->stack.states[0];
    x->stack.depth--;
    memmove(    &x->stack.remainings[0], 
                &x->stack.remainings[1], 
                x->stack.depth * sizeof(x->stack.remainings[0]));
    memmove(    &x->stack.states[0], 
                &x->stack.states[1], 
                x->stack.depth * sizeof(x->stack.states[0]));
    return next_state;
}