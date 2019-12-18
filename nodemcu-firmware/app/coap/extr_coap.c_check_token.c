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
struct TYPE_5__ {scalar_t__ len; int /*<<< orphan*/  p; } ;
struct TYPE_6__ {TYPE_1__ tok; } ;
typedef  TYPE_2__ coap_packet_t ;
struct TYPE_7__ {scalar_t__ len; int /*<<< orphan*/  p; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_3__ the_token ; 

int
check_token(coap_packet_t *pkt) {
  return pkt->tok.len == the_token.len && memcmp(pkt->tok.p, the_token.p, the_token.len) == 0;
}