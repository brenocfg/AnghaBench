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
typedef  int /*<<< orphan*/  PROPERTY_DEFINITION ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pd_free(PROPERTY_DEFINITION *pd)
{
    OPENSSL_free(pd);
}