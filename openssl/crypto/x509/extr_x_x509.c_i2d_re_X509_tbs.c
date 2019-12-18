#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int modified; } ;
struct TYPE_7__ {TYPE_1__ enc; } ;
struct TYPE_6__ {TYPE_4__ cert_info; } ;
typedef  TYPE_2__ X509 ;

/* Variables and functions */
 int i2d_X509_CINF (TYPE_4__*,unsigned char**) ; 

int i2d_re_X509_tbs(X509 *x, unsigned char **pp)
{
    x->cert_info.enc.modified = 1;
    return i2d_X509_CINF(&x->cert_info, pp);
}