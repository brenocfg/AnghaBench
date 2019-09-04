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
struct TYPE_4__ {int cmd; int authenticated; } ;
typedef  TYPE_1__ conn ;
struct TYPE_5__ {int verbose; int /*<<< orphan*/  sasl; } ;

/* Variables and functions */
#define  PROTOCOL_BINARY_CMD_SASL_AUTH 131 
#define  PROTOCOL_BINARY_CMD_SASL_LIST_MECHS 130 
#define  PROTOCOL_BINARY_CMD_SASL_STEP 129 
#define  PROTOCOL_BINARY_CMD_VERSION 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 TYPE_2__ settings ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static bool authenticated(conn *c) {
    assert(settings.sasl);
    bool rv = false;

    switch (c->cmd) {
    case PROTOCOL_BINARY_CMD_SASL_LIST_MECHS: /* FALLTHROUGH */
    case PROTOCOL_BINARY_CMD_SASL_AUTH:       /* FALLTHROUGH */
    case PROTOCOL_BINARY_CMD_SASL_STEP:       /* FALLTHROUGH */
    case PROTOCOL_BINARY_CMD_VERSION:         /* FALLTHROUGH */
        rv = true;
        break;
    default:
        rv = c->authenticated;
    }

    if (settings.verbose > 1) {
        fprintf(stderr, "authenticated() in cmd 0x%02x is %s\n",
                c->cmd, rv ? "true" : "false");
    }

    return rv;
}