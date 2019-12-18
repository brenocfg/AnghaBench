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
struct SpnegoDecode {int /*<<< orphan*/  x509; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_push (int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  memset (struct SpnegoDecode*,int /*<<< orphan*/ ,int) ; 

void
spnego_decode_init(struct SpnegoDecode *x, size_t length)
{
    memset(x, 0, sizeof(*x));
    
    ASN1_push(x->x509, 0xFFFFFFFF, length);
}