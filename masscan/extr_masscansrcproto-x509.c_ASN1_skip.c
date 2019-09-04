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
struct TYPE_2__ {unsigned int* remainings; } ;
struct CertDecode {TYPE_1__ stack; } ;

/* Variables and functions */

__attribute__((used)) static unsigned
ASN1_skip(struct CertDecode *x, unsigned *i, size_t length)
{
    unsigned len;

    if (x->stack.remainings[0] == 0)
        return 1;
    
    /* bytes remaining in packet */
    len = (unsigned)(length - (*i) - 1);

    /* bytes remaining in field */
    if (len > x->stack.remainings[0])
        len = x->stack.remainings[0];

    /* increment 'offset' by this length */
    (*i) += len;

    /* decrement 'remaining' by this length */
    x->stack.remainings[0] = (unsigned short)(x->stack.remainings[0] - len);

    return x->stack.remainings[0] == 0;
    
}