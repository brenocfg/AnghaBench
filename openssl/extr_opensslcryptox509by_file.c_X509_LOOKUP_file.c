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
typedef  int /*<<< orphan*/  X509_LOOKUP_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  x509_file_lookup ; 

X509_LOOKUP_METHOD *X509_LOOKUP_file(void)
{
    return &x509_file_lookup;
}