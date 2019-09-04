#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  coap_rw_buffer_t ;
struct TYPE_5__ {int /*<<< orphan*/  tok; } ;
typedef  TYPE_1__ coap_packet_t ;
typedef  int /*<<< orphan*/  coap_endpoint_t ;

/* Variables and functions */
 int /*<<< orphan*/  COAP_CONTENTTYPE_TEXT_PLAIN ; 
 int /*<<< orphan*/  COAP_RSPCODE_CONTENT ; 
 int coap_make_response (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  id ; 
 int /*<<< orphan*/  system_get_chip_id () ; 

__attribute__((used)) static int handle_get_id(const coap_endpoint_t *ep, coap_rw_buffer_t *scratch, const coap_packet_t *inpkt, coap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
    id = system_get_chip_id();
    return coap_make_response(scratch, outpkt, (const uint8_t *)(&id), sizeof(uint32_t), id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CONTENT, COAP_CONTENTTYPE_TEXT_PLAIN);
}