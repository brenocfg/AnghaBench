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
typedef  scalar_t__ i2c_status_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_ADDR (int) ; 
 scalar_t__ I2C_STATUS_SUCCESS ; 
 int /*<<< orphan*/  I2C_TIMEOUT ; 
 int ROWS_PER_HAND ; 
 scalar_t__ TWI_REPLY_KEYDATA ; 
 scalar_t__ i2c_receive (int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 scalar_t__* rows ; 

__attribute__((used)) static int i2c_read_hand(int hand) {
  uint8_t buf[5];
  i2c_status_t ret = i2c_receive(I2C_ADDR(hand), buf, sizeof(buf), I2C_TIMEOUT);
  if (ret != I2C_STATUS_SUCCESS)
    return 1;

  if (buf[0] != TWI_REPLY_KEYDATA)
    return 2;

  int start_row = hand ? ROWS_PER_HAND : 0;
  uint8_t *out = &rows[start_row];
  memcpy(out, &buf[1], 4);
  return 0;
}