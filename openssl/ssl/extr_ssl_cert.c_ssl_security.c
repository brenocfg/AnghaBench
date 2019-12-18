#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* cert; } ;
struct TYPE_5__ {int (* sec_cb ) (TYPE_2__ const*,int /*<<< orphan*/ *,int,int,int,void*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  sec_ex; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int stub1 (TYPE_2__ const*,int /*<<< orphan*/ *,int,int,int,void*,int /*<<< orphan*/ ) ; 

int ssl_security(const SSL *s, int op, int bits, int nid, void *other)
{
    return s->cert->sec_cb(s, NULL, op, bits, nid, other, s->cert->sec_ex);
}