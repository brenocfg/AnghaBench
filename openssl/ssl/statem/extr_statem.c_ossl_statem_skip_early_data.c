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
struct TYPE_6__ {scalar_t__ hand_state; } ;
struct TYPE_5__ {scalar_t__ early_data; } ;
struct TYPE_7__ {scalar_t__ hello_retry_request; TYPE_2__ statem; int /*<<< orphan*/  server; TYPE_1__ ext; } ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 scalar_t__ SSL_EARLY_DATA_REJECTED ; 
 scalar_t__ SSL_HRR_COMPLETE ; 
 scalar_t__ TLS_ST_EARLY_DATA ; 

int ossl_statem_skip_early_data(SSL *s)
{
    if (s->ext.early_data != SSL_EARLY_DATA_REJECTED)
        return 0;

    if (!s->server
            || s->statem.hand_state != TLS_ST_EARLY_DATA
            || s->hello_retry_request == SSL_HRR_COMPLETE)
        return 0;

    return 1;
}