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
 int /*<<< orphan*/  BIO_meth_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  method_tls_dump ; 

void bio_f_tls_dump_filter_free(void)
{
    BIO_meth_free(method_tls_dump);
}