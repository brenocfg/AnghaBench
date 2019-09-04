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
struct TYPE_3__ {char* sname; } ;
typedef  TYPE_1__ X509_PURPOSE ;

/* Variables and functions */

char *X509_PURPOSE_get0_sname(const X509_PURPOSE *xp)
{
    return xp->sname;
}