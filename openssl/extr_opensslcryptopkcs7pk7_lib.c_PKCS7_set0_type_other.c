#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * other; } ;
struct TYPE_5__ {TYPE_1__ d; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ PKCS7 ;
typedef  int /*<<< orphan*/  ASN1_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_nid2obj (int) ; 

int PKCS7_set0_type_other(PKCS7 *p7, int type, ASN1_TYPE *other)
{
    p7->type = OBJ_nid2obj(type);
    p7->d.other = other;
    return 1;
}