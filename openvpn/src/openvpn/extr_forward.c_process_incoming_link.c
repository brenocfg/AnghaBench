#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct link_socket_info {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;
struct TYPE_4__ {TYPE_1__ buf; } ;
struct context {TYPE_2__ c2; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_PROC_IN_LINK ; 
 struct link_socket_info* get_link_socket_info (struct context*) ; 
 int /*<<< orphan*/  perf_pop () ; 
 int /*<<< orphan*/  perf_push (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_incoming_link_part1 (struct context*,struct link_socket_info*,int) ; 
 int /*<<< orphan*/  process_incoming_link_part2 (struct context*,struct link_socket_info*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
process_incoming_link(struct context *c)
{
    perf_push(PERF_PROC_IN_LINK);

    struct link_socket_info *lsi = get_link_socket_info(c);
    const uint8_t *orig_buf = c->c2.buf.data;

    process_incoming_link_part1(c, lsi, false);
    process_incoming_link_part2(c, lsi, orig_buf);

    perf_pop();
}