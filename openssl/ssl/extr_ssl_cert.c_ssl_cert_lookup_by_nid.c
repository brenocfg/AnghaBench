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
struct TYPE_3__ {int nid; } ;

/* Variables and functions */
 size_t OSSL_NELEM (TYPE_1__*) ; 
 TYPE_1__* ssl_cert_info ; 

int ssl_cert_lookup_by_nid(int nid, size_t *pidx)
{
    size_t i;

    for (i = 0; i < OSSL_NELEM(ssl_cert_info); i++) {
        if (ssl_cert_info[i].nid == nid) {
            *pidx = i;
            return 1;
        }
    }

    return 0;
}