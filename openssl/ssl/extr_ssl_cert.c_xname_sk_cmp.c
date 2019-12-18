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
typedef  int /*<<< orphan*/  X509_NAME ;

/* Variables and functions */
 int xname_cmp (int /*<<< orphan*/  const* const,int /*<<< orphan*/  const* const) ; 

__attribute__((used)) static int xname_sk_cmp(const X509_NAME *const *a, const X509_NAME *const *b)
{
    return xname_cmp(*a, *b);
}