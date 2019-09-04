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
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 int check_ca (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x509v3_cache_extensions (int /*<<< orphan*/ *) ; 

int X509_check_ca(X509 *x)
{
    x509v3_cache_extensions(x);

    return check_ca(x);
}