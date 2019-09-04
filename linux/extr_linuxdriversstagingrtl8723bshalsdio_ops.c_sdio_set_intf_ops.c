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
struct adapter {int dummy; } ;
struct _io_ops {int /*<<< orphan*/  _sd_f0_read8; int /*<<< orphan*/ * _write_port; int /*<<< orphan*/ * _write_mem; int /*<<< orphan*/ * _writeN; int /*<<< orphan*/ * _write32; int /*<<< orphan*/ * _write16; int /*<<< orphan*/ * _write8; int /*<<< orphan*/ * _read_port; int /*<<< orphan*/ * _read_mem; int /*<<< orphan*/ * _read32; int /*<<< orphan*/ * _read16; int /*<<< orphan*/ * _read8; } ;

/* Variables and functions */
 int /*<<< orphan*/  sdio_f0_read8 ; 
 int /*<<< orphan*/  sdio_read16 ; 
 int /*<<< orphan*/  sdio_read32 ; 
 int /*<<< orphan*/  sdio_read8 ; 
 int /*<<< orphan*/  sdio_read_mem ; 
 int /*<<< orphan*/  sdio_read_port ; 
 int /*<<< orphan*/  sdio_write16 ; 
 int /*<<< orphan*/  sdio_write32 ; 
 int /*<<< orphan*/  sdio_write8 ; 
 int /*<<< orphan*/  sdio_writeN ; 
 int /*<<< orphan*/  sdio_write_mem ; 
 int /*<<< orphan*/  sdio_write_port ; 

void sdio_set_intf_ops(struct adapter *adapter, struct _io_ops *ops)
{
	ops->_read8 = &sdio_read8;
	ops->_read16 = &sdio_read16;
	ops->_read32 = &sdio_read32;
	ops->_read_mem = &sdio_read_mem;
	ops->_read_port = &sdio_read_port;

	ops->_write8 = &sdio_write8;
	ops->_write16 = &sdio_write16;
	ops->_write32 = &sdio_write32;
	ops->_writeN = &sdio_writeN;
	ops->_write_mem = &sdio_write_mem;
	ops->_write_port = &sdio_write_port;

	ops->_sd_f0_read8 = sdio_f0_read8;
}