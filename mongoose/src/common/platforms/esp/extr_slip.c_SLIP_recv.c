#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  char uint8_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 char uart_rx_one_char_block () ; 

uint32_t SLIP_recv(void *pkt, uint32_t max_len) {
  uint8_t c;
  uint32_t len = 0;
  uint8_t *p = (uint8_t *) pkt;
  do {
    c = uart_rx_one_char_block();
  } while (c != '\xc0');
  while (len < max_len) {
    c = uart_rx_one_char_block();
    if (c == '\xc0') return len;
    if (c == '\xdb') {
      c = uart_rx_one_char_block();
      if (c == '\xdc') {
        c = '\xc0';
      } else if (c == '\xdd') {
        c = '\xdb';
      } else {
        len = 0;
        break; /* Bad esc sequence. */
      }
    }
    *p++ = c;
    len++;
  }
  do {
    c = uart_rx_one_char_block();
  } while (c != '\xc0');
  return len;
}