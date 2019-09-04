#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int renegotiate; } ;
struct TYPE_5__ {TYPE_1__ s3; int /*<<< orphan*/ * handshake_func; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */

int ssl3_renegotiate(SSL *s)
{
    if (s->handshake_func == NULL)
        return 1;

    s->s3.renegotiate = 1;
    return 1;
}