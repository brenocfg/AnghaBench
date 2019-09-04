#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int type; int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ASN1_INTEGER ;

/* Variables and functions */
 int V_ASN1_NEG ; 
 int i2c_ibuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned char**) ; 

int i2c_ASN1_INTEGER(ASN1_INTEGER *a, unsigned char **pp)
{
    return i2c_ibuf(a->data, a->length, a->type & V_ASN1_NEG, pp);
}