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
struct TYPE_3__ {int trust; } ;
typedef  TYPE_1__ X509_TRUST ;

/* Variables and functions */
 int X509_TRUST_COUNT ; 
 int X509_TRUST_MAX ; 
 int X509_TRUST_MIN ; 
 int sk_X509_TRUST_find (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * trtable ; 

int X509_TRUST_get_by_id(int id)
{
    X509_TRUST tmp;
    int idx;

    if ((id >= X509_TRUST_MIN) && (id <= X509_TRUST_MAX))
        return id - X509_TRUST_MIN;
    if (trtable == NULL)
        return -1;
    tmp.trust = id;
    idx = sk_X509_TRUST_find(trtable, &tmp);
    if (idx < 0)
        return -1;
    return idx + X509_TRUST_COUNT;
}