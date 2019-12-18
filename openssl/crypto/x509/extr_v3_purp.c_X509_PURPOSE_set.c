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
 int /*<<< orphan*/  X509V3_F_X509_PURPOSE_SET ; 
 int /*<<< orphan*/  X509V3_R_INVALID_PURPOSE ; 
 int /*<<< orphan*/  X509V3err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int X509_PURPOSE_get_by_id (int) ; 

int X509_PURPOSE_set(int *p, int purpose)
{
    if (X509_PURPOSE_get_by_id(purpose) == -1) {
        X509V3err(X509V3_F_X509_PURPOSE_SET, X509V3_R_INVALID_PURPOSE);
        return 0;
    }
    *p = purpose;
    return 1;
}