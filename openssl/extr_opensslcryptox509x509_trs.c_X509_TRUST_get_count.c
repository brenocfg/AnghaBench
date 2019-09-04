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

/* Variables and functions */
 int X509_TRUST_COUNT ; 
 int sk_X509_TRUST_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trtable ; 

int X509_TRUST_get_count(void)
{
    if (!trtable)
        return X509_TRUST_COUNT;
    return sk_X509_TRUST_num(trtable) + X509_TRUST_COUNT;
}