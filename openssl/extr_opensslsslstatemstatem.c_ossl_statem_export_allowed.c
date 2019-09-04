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
struct TYPE_5__ {scalar_t__ previous_server_finished_len; } ;
struct TYPE_7__ {TYPE_2__ statem; TYPE_1__ s3; } ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 scalar_t__ TLS_ST_SW_FINISHED ; 

int ossl_statem_export_allowed(SSL *s)
{
    return s->s3.previous_server_finished_len != 0
           && s->statem.hand_state != TLS_ST_SW_FINISHED;
}