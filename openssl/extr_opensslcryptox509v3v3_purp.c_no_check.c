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
typedef  int /*<<< orphan*/  X509_PURPOSE ;
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */

__attribute__((used)) static int no_check(const X509_PURPOSE *xp, const X509 *x, int ca)
{
    return 1;
}