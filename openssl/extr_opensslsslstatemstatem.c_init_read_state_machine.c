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
struct TYPE_5__ {int /*<<< orphan*/  read_state; } ;
struct TYPE_4__ {TYPE_2__ statem; } ;
typedef  TYPE_1__ SSL ;
typedef  TYPE_2__ OSSL_STATEM ;

/* Variables and functions */
 int /*<<< orphan*/  READ_STATE_HEADER ; 

__attribute__((used)) static void init_read_state_machine(SSL *s)
{
    OSSL_STATEM *st = &s->statem;

    st->read_state = READ_STATE_HEADER;
}