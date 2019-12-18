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
struct TYPE_2__ {int /*<<< orphan*/  max_length; } ;
struct TCP_Control_Block {TYPE_1__ banout; int /*<<< orphan*/  banner1_state; } ;
struct TCP_ConnectionTable {int /*<<< orphan*/  banner1; } ;
struct InteractiveData {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  banner1_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char const*,size_t,TYPE_1__*,struct InteractiveData*) ; 

__attribute__((used)) static size_t
parse_banner(
    struct TCP_ConnectionTable *tcpcon,
    struct TCP_Control_Block *tcb,
    const unsigned char *payload,
    size_t payload_length,
    struct InteractiveData *more)
{
    assert(tcb->banout.max_length);
    
    banner1_parse(
                                    tcpcon->banner1,
                                    &tcb->banner1_state,
                                    payload,
                                    payload_length,
                                    &tcb->banout,
                                    more);
    return payload_length;
}