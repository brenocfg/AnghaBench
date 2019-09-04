#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sname; } ;
typedef  TYPE_1__ X509_PURPOSE ;

/* Variables and functions */
 TYPE_1__* X509_PURPOSE_get0 (int) ; 
 int X509_PURPOSE_get_count () ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

int X509_PURPOSE_get_by_sname(const char *sname)
{
    int i;
    X509_PURPOSE *xptmp;
    for (i = 0; i < X509_PURPOSE_get_count(); i++) {
        xptmp = X509_PURPOSE_get0(i);
        if (strcmp(xptmp->sname, sname) == 0)
            return i;
    }
    return -1;
}