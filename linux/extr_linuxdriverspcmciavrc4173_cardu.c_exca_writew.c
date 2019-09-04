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
struct TYPE_3__ {scalar_t__ base; } ;
typedef  TYPE_1__ vrc4173_socket_t ;
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 scalar_t__ EXCA_REGS_BASE ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void exca_writew(vrc4173_socket_t *socket, uint8_t offset, uint16_t val)
{
	writeb((u8)val, socket->base + EXCA_REGS_BASE + offset);
	writeb((u8)(val >> 8), socket->base + EXCA_REGS_BASE + offset + 1);
}