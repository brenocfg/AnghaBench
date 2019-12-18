#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tls_multi {scalar_t__ locked_cert_hash_set; TYPE_1__* session; } ;
struct cert_hash_set {int dummy; } ;
struct TYPE_2__ {struct cert_hash_set* cert_hash_set; } ;

/* Variables and functions */
 size_t TM_ACTIVE ; 
 scalar_t__ cert_hash_copy (struct cert_hash_set const*) ; 

void
tls_lock_cert_hash_set(struct tls_multi *multi)
{
    const struct cert_hash_set *chs = multi->session[TM_ACTIVE].cert_hash_set;
    if (chs && !multi->locked_cert_hash_set)
    {
        multi->locked_cert_hash_set = cert_hash_copy(chs);
    }
}