#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int opcode; } ;
struct TYPE_8__ {TYPE_1__ request; } ;
struct TYPE_9__ {int sfd; int /*<<< orphan*/  write_and_go; TYPE_2__ binary_header; } ;
typedef  TYPE_3__ conn ;
struct TYPE_10__ {scalar_t__ verbose; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROTOCOL_BINARY_RESPONSE_EINVAL ; 
 int /*<<< orphan*/  conn_closing ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 TYPE_5__ settings ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  write_bin_error (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_binary_protocol_error(conn *c) {
    write_bin_error(c, PROTOCOL_BINARY_RESPONSE_EINVAL, NULL, 0);
    if (settings.verbose) {
        fprintf(stderr, "Protocol error (opcode %02x), close connection %d\n",
                c->binary_header.request.opcode, c->sfd);
    }
    c->write_and_go = conn_closing;
}