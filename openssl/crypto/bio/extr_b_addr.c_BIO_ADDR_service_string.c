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
typedef  int /*<<< orphan*/  BIO_ADDR ;

/* Variables and functions */
 scalar_t__ addr_strings (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,char**) ; 

char *BIO_ADDR_service_string(const BIO_ADDR *ap, int numeric)
{
    char *service = NULL;

    if (addr_strings(ap, numeric, NULL, &service))
        return service;

    return NULL;
}