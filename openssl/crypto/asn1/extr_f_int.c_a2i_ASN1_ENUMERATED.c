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
struct TYPE_4__ {int type; } ;
typedef  int /*<<< orphan*/  BIO ;
typedef  TYPE_1__ ASN1_ENUMERATED ;

/* Variables and functions */
 int V_ASN1_INTEGER ; 
 int V_ASN1_NEG ; 
 int a2i_ASN1_INTEGER (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 

int a2i_ASN1_ENUMERATED(BIO *bp, ASN1_ENUMERATED *bs, char *buf, int size)
{
    int rv = a2i_ASN1_INTEGER(bp, bs, buf, size);
    if (rv == 1)
        bs->type = V_ASN1_INTEGER | (bs->type & V_ASN1_NEG);
    return rv;
}