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
 scalar_t__ ASN1_STRING_get0_data (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static const char *print_time(const ASN1_TIME *t)
{
    return t == NULL ? "<null>" : (const char *)ASN1_STRING_get0_data(t);
}