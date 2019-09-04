#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
typedef  int uint16 ;
struct sniffer_buf2 {scalar_t__ buf; } ;
struct TYPE_3__ {int len; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ packet_t ;
typedef  int /*<<< orphan*/  management_request_t ;
typedef  int /*<<< orphan*/  ETSParam ;

/* Variables and functions */
 int /*<<< orphan*/  c_free (TYPE_1__*) ; 
 scalar_t__ c_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int mon_mask ; 
 int mon_offset ; 
 int mon_value ; 
 int /*<<< orphan*/  task_post_medium (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasknumber ; 

__attribute__((used)) static void wifi_rx_cb(uint8 *buf, uint16 len) {
  if (len != sizeof(struct sniffer_buf2)) {
    return;
  }

  struct sniffer_buf2 *snb = (struct sniffer_buf2 *) buf;
  management_request_t *mgt = (management_request_t *) snb->buf;

  if (mon_offset > len) {
    return;
  }

  if ((buf[mon_offset] & mon_mask) != mon_value) {
    return;
  }

  packet_t *packet = (packet_t *) c_malloc(len + sizeof(packet_t));
  if (packet) {
    packet->len = len;
    memcpy(packet->buf, buf, len);
    if (!task_post_medium(tasknumber, (ETSParam) packet)) {
      c_free(packet);
    }
  }
}