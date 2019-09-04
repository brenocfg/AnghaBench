#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * peer_ca_names; } ;
struct TYPE_6__ {TYPE_1__ tmp; } ;
struct TYPE_7__ {TYPE_2__ s3; } ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  X509_NAME_free ; 
 int /*<<< orphan*/  sk_X509_NAME_pop_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_certificate_authorities(SSL *s, unsigned int context)
{
    sk_X509_NAME_pop_free(s->s3.tmp.peer_ca_names, X509_NAME_free);
    s->s3.tmp.peer_ca_names = NULL;
    return 1;
}