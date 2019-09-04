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
typedef  scalar_t__ uint8_t ;
typedef  void* uint32_t ;
struct data_buf {scalar_t__ flags; } ;
struct TYPE_2__ {int state; size_t bwi; int /*<<< orphan*/  ps; struct data_buf* bufs; } ;

/* Variables and functions */
#define  READ_DATA 132 
#define  READ_ERROR 131 
#define  READ_FLAGS 130 
 void* READ_PERI_REG (int /*<<< orphan*/ ) ; 
#define  READ_UNESCAPE 129 
#define  READ_WAIT_START 128 
 int /*<<< orphan*/  SET_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_FIFO_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_INT_CLR_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_INT_ENA_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_INT_ST_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_STATUS_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_PERI_REG (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  add_byte (scalar_t__) ; 
 int /*<<< orphan*/  next_write_buf () ; 
 TYPE_1__ ub ; 

void uart_isr(void *arg) {
  uint32_t int_st = READ_PERI_REG(UART_INT_ST_REG(0));
  uint8_t fifo_len, i;
  while ((fifo_len = READ_PERI_REG(UART_STATUS_REG(0))) > 0) {
    for (i = 0; i < fifo_len; i++) {
      uint8_t byte = READ_PERI_REG(UART_FIFO_REG(0));
      switch (ub.state) {
        case READ_WAIT_START: {
          if (byte == 0xc0) {
            ub.state = READ_FLAGS;
            ub.ps = 0;
          }
          break;
        }
        case READ_FLAGS:
        case READ_DATA: {
          struct data_buf *buf = &ub.bufs[ub.bwi];
          if (byte == 0xdb) {
            ub.state = READ_UNESCAPE;
          } else if (byte == 0xc0) {
            next_write_buf();
            if (ub.ps == 0) {
              /* Empty packet, sender aborted. */
              ub.state = READ_ERROR;
              SET_PERI_REG_MASK(UART_INT_ENA_REG(0), 0);
              goto out;
            } else {
              ub.state = READ_WAIT_START;
            }
          } else {
            if (ub.state == READ_FLAGS) {
              buf->flags = byte;
              ub.state = READ_DATA;
            } else {
              add_byte(byte);
            }
          }
          break;
        }
        case READ_UNESCAPE: {
          if (byte == 0xdc) {
            byte = 0xc0;
          } else if (byte == 0xdd) {
            byte = 0xdb;
          } else {
            ub.state = READ_ERROR;
            SET_PERI_REG_MASK(UART_INT_ENA_REG(0), 0);
            goto out;
          }
          add_byte(byte);
          ub.state = READ_DATA;
          break;
        }
        case READ_ERROR: {
          goto out;
        }
      }
    }
  }
out:
  WRITE_PERI_REG(UART_INT_CLR_REG(0), int_st);
  (void) arg;
}