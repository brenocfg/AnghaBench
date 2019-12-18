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
 int /*<<< orphan*/  sk_X509_PURPOSE_pop_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xptable ; 
 int /*<<< orphan*/  xptable_free ; 

void X509_PURPOSE_cleanup(void)
{
    sk_X509_PURPOSE_pop_free(xptable, xptable_free);
    xptable = NULL;
}