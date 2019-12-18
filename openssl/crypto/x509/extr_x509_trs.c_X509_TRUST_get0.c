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
typedef  int /*<<< orphan*/  X509_TRUST ;

/* Variables and functions */
 scalar_t__ X509_TRUST_COUNT ; 
 int /*<<< orphan*/ * sk_X509_TRUST_value (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * trstandard ; 
 int /*<<< orphan*/  trtable ; 

X509_TRUST *X509_TRUST_get0(int idx)
{
    if (idx < 0)
        return NULL;
    if (idx < (int)X509_TRUST_COUNT)
        return trstandard + idx;
    return sk_X509_TRUST_value(trtable, idx - X509_TRUST_COUNT);
}