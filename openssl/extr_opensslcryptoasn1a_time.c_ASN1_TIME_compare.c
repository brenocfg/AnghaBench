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
 int /*<<< orphan*/  ASN1_TIME_diff (int*,int*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

int ASN1_TIME_compare(const ASN1_TIME *a, const ASN1_TIME *b)
{
    int day, sec;

    if (!ASN1_TIME_diff(&day, &sec, b, a))
        return -2;
    if (day > 0 || sec > 0)
        return 1;
    if (day < 0 || sec < 0)
        return -1;
    return 0;
}