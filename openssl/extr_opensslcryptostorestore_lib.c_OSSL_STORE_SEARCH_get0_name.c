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
typedef  int /*<<< orphan*/  X509_NAME ;
struct TYPE_3__ {int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ OSSL_STORE_SEARCH ;

/* Variables and functions */

X509_NAME *OSSL_STORE_SEARCH_get0_name(OSSL_STORE_SEARCH *criterion)
{
    return criterion->name;
}