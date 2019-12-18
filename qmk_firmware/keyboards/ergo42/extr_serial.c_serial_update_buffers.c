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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int SERIAL_DELAY ; 
 int SERIAL_MASTER_BUFFER_LENGTH ; 
 int SERIAL_SLAVE_BUFFER_LENGTH ; 
 int /*<<< orphan*/  _delay_us (int) ; 
 int /*<<< orphan*/  cli () ; 
 int /*<<< orphan*/  sei () ; 
 int /*<<< orphan*/  serial_high () ; 
 int /*<<< orphan*/  serial_input () ; 
 int /*<<< orphan*/  serial_low () ; 
 scalar_t__* serial_master_buffer ; 
 int /*<<< orphan*/  serial_output () ; 
 scalar_t__ serial_read_byte () ; 
 scalar_t__ serial_read_pin () ; 
 scalar_t__* serial_slave_buffer ; 
 int /*<<< orphan*/  serial_write_byte (scalar_t__) ; 
 int /*<<< orphan*/  sync_recv () ; 

int serial_update_buffers(void) {
  // this code is very time dependent, so we need to disable interrupts
  cli();

  // signal to the slave that we want to start a transaction
  serial_output();
  serial_low();
  _delay_us(1);

  // wait for the slaves response
  serial_input();
  serial_high();
  _delay_us(SERIAL_DELAY);

  // check if the slave is present
  if (serial_read_pin()) {
    // slave failed to pull the line low, assume not present
    sei();
    return 1;
  }

  // if the slave is present syncronize with it
  sync_recv();

  uint8_t checksum_computed = 0;
  // receive data from the slave
  for (int i = 0; i < SERIAL_SLAVE_BUFFER_LENGTH; ++i) {
    serial_slave_buffer[i] = serial_read_byte();
    sync_recv();
    checksum_computed += serial_slave_buffer[i];
  }
  uint8_t checksum_received = serial_read_byte();
  sync_recv();

  if (checksum_computed != checksum_received) {
    sei();
    return 1;
  }

  uint8_t checksum = 0;
  // send data to the slave
  for (int i = 0; i < SERIAL_MASTER_BUFFER_LENGTH; ++i) {
    serial_write_byte(serial_master_buffer[i]);
    sync_recv();
    checksum += serial_master_buffer[i];
  }
  serial_write_byte(checksum);
  sync_recv();

  // always, release the line when not in use
  serial_output();
  serial_high();

  sei();
  return 0;
}