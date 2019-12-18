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
 int /*<<< orphan*/  BIO_vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONF_modules_unload (int) ; 
 int /*<<< orphan*/  NCONF_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conf ; 
 int /*<<< orphan*/  in ; 

void cleanup_tests(void)
{
    BIO_vfree(in);
    NCONF_free(conf);
    CONF_modules_unload(1);
}