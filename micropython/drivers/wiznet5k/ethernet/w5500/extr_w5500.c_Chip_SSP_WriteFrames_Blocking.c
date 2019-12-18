#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* _write_bytes ) (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__ SPI; } ;
struct TYPE_6__ {TYPE_2__ IF; } ;

/* Variables and functions */
 TYPE_3__ WIZCHIP ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Chip_SSP_WriteFrames_Blocking(int dummy, const uint8_t *buf, uint32_t len) {
    WIZCHIP.IF.SPI._write_bytes(buf, len);
}