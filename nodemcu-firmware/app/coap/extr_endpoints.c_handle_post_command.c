#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  coap_rw_buffer_t ;
struct TYPE_7__ {scalar_t__ len; } ;
struct TYPE_6__ {int /*<<< orphan*/  tok; TYPE_5__ payload; } ;
typedef  TYPE_1__ coap_packet_t ;
typedef  int /*<<< orphan*/  coap_endpoint_t ;

/* Variables and functions */
 int /*<<< orphan*/  COAP_CONTENTTYPE_TEXT_PLAIN ; 
 int /*<<< orphan*/  COAP_RSPCODE_BAD_REQUEST ; 
 int /*<<< orphan*/  COAP_RSPCODE_CONTENT ; 
 int LUA_MAXINPUT ; 
 int /*<<< orphan*/  LUA_PROCESS_LINE_SIG ; 
 int /*<<< orphan*/  LUA_TASK_PRIO ; 
 int /*<<< orphan*/  NODE_DBG (char*) ; 
 int /*<<< orphan*/  coap_buffer_to_string (char*,int,TYPE_5__*) ; 
 int coap_make_response (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_put_line (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  system_os_post (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_post_command(const coap_endpoint_t *ep, coap_rw_buffer_t *scratch, const coap_packet_t *inpkt, coap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
    if (inpkt->payload.len == 0)
        return coap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_BAD_REQUEST, COAP_CONTENTTYPE_TEXT_PLAIN);
    if (inpkt->payload.len > 0)
    {
        char line[LUA_MAXINPUT];
        if (!coap_buffer_to_string(line, LUA_MAXINPUT, &inpkt->payload) &&
            lua_put_line(line, strlen(line))) {
            NODE_DBG("\nResult(if any):\n");
            system_os_post (LUA_TASK_PRIO, LUA_PROCESS_LINE_SIG, 0);
        }
        return coap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CONTENT, COAP_CONTENTTYPE_TEXT_PLAIN);
    }
}