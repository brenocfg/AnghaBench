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
typedef  int /*<<< orphan*/  ASN1_TIME ;

/* Variables and functions */
 int X509_cmp_time (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int X509_cmp_current_time(const ASN1_TIME *ctm)
{
    return X509_cmp_time(ctm, NULL);
}