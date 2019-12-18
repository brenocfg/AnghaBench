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
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  ERR_print_errors_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  openssl_error_cb ; 

__attribute__((used)) static void finalize(int success)
{
    if (success)
        ERR_clear_error();
    else
        ERR_print_errors_cb(openssl_error_cb, NULL);
}