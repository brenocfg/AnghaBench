#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* sigalg; } ;
struct TYPE_8__ {TYPE_2__ tmp; } ;
struct TYPE_9__ {TYPE_3__ s3; } ;
struct TYPE_6__ {int sig; } ;
typedef  TYPE_4__ SSL ;

/* Variables and functions */

int SSL_get_signature_type_nid(const SSL *s, int *pnid)
{
    if (s->s3.tmp.sigalg == NULL)
        return 0;
    *pnid = s->s3.tmp.sigalg->sig;
    return 1;
}