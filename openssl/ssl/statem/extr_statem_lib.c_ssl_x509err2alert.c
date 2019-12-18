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
struct TYPE_3__ {int x509err; int alert; } ;
typedef  TYPE_1__ X509ERR2ALERT ;

/* Variables and functions */
 int X509_V_OK ; 
 TYPE_1__* x509table ; 

int ssl_x509err2alert(int x509err)
{
    const X509ERR2ALERT *tp;

    for (tp = x509table; tp->x509err != X509_V_OK; ++tp)
        if (tp->x509err == x509err)
            break;
    return tp->alert;
}