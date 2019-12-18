#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  mp_obj_base_t ;
struct TYPE_5__ {int len; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ mp_machine_i2c_buf_t ;
struct TYPE_6__ {int /*<<< orphan*/  port; } ;
typedef  TYPE_2__ machine_hw_i2c_obj_t ;
typedef  int /*<<< orphan*/  i2c_cmd_handle_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_TIMEOUT ; 
 scalar_t__ ESP_FAIL ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  I2C_MASTER_ACK ; 
 int /*<<< orphan*/  I2C_MASTER_LAST_NACK ; 
 int MP_ENODEV ; 
 int MP_ETIMEDOUT ; 
 unsigned int MP_MACHINE_I2C_FLAG_READ ; 
 unsigned int MP_MACHINE_I2C_FLAG_STOP ; 
 TYPE_2__* MP_OBJ_TO_PTR (int /*<<< orphan*/ *) ; 
 int abs (scalar_t__) ; 
 int /*<<< orphan*/  i2c_cmd_link_create () ; 
 int /*<<< orphan*/  i2c_cmd_link_delete (int /*<<< orphan*/ ) ; 
 scalar_t__ i2c_master_cmd_begin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_master_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_master_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_master_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_master_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  i2c_master_write_byte (int /*<<< orphan*/ ,int,int) ; 
 int portTICK_RATE_MS ; 

int machine_hw_i2c_transfer(mp_obj_base_t *self_in, uint16_t addr, size_t n, mp_machine_i2c_buf_t *bufs, unsigned int flags) {
    machine_hw_i2c_obj_t *self = MP_OBJ_TO_PTR(self_in);

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, addr << 1 | (flags & MP_MACHINE_I2C_FLAG_READ), true);

    int data_len = 0;
    for (; n--; ++bufs) {
        if (flags & MP_MACHINE_I2C_FLAG_READ) {
            i2c_master_read(cmd, bufs->buf, bufs->len, n == 0 ? I2C_MASTER_LAST_NACK : I2C_MASTER_ACK);
        } else {
            if (bufs->len != 0) {
                i2c_master_write(cmd, bufs->buf, bufs->len, true);
            }
        }
        data_len += bufs->len;
    }

    if (flags & MP_MACHINE_I2C_FLAG_STOP) {
        i2c_master_stop(cmd);
    }

    // TODO proper timeout
    esp_err_t err = i2c_master_cmd_begin(self->port, cmd, 100 * (1 + data_len) / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

    if (err == ESP_FAIL) {
        return -MP_ENODEV;
    } else if (err == ESP_ERR_TIMEOUT) {
        return -MP_ETIMEDOUT;
    } else if (err != ESP_OK) {
        return -abs(err);
    }

    return data_len;
}