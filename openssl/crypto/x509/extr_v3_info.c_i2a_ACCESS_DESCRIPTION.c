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
struct TYPE_3__ {int /*<<< orphan*/  method; } ;
typedef  int /*<<< orphan*/  BIO ;
typedef  TYPE_1__ ACCESS_DESCRIPTION ;

/* Variables and functions */
 int /*<<< orphan*/  i2a_ASN1_OBJECT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int i2a_ACCESS_DESCRIPTION(BIO *bp, const ACCESS_DESCRIPTION *a)
{
    i2a_ASN1_OBJECT(bp, a->method);
    return 2;
}