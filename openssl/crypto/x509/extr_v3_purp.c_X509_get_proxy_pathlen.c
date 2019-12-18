#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ex_flags; long ex_pcpathlen; } ;
typedef  TYPE_1__ X509 ;

/* Variables and functions */
 int EXFLAG_PROXY ; 
 int X509_check_purpose (TYPE_1__*,int,int) ; 

long X509_get_proxy_pathlen(X509 *x)
{
    /* Called for side effect of caching extensions */
    if (X509_check_purpose(x, -1, -1) != 1
            || (x->ex_flags & EXFLAG_PROXY) == 0)
        return -1;
    return x->ex_pcpathlen;
}