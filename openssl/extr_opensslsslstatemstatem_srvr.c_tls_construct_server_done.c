#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_6__ {int /*<<< orphan*/  cert_request; } ;
struct TYPE_7__ {TYPE_1__ tmp; } ;
struct TYPE_8__ {TYPE_2__ s3; } ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ssl3_digest_cached_records (TYPE_3__*,int /*<<< orphan*/ ) ; 

int tls_construct_server_done(SSL *s, WPACKET *pkt)
{
    if (!s->s3.tmp.cert_request) {
        if (!ssl3_digest_cached_records(s, 0)) {
            /* SSLfatal() already called */
            return 0;
        }
    }
    return 1;
}