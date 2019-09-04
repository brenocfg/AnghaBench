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
typedef  int /*<<< orphan*/  u8 ;
struct yenta_socket {unsigned int base; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug (char*,struct yenta_socket*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readb (unsigned int) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void exca_writeb(struct yenta_socket *socket, unsigned reg, u8 val)
{
	debug("%04x %02x\n", socket, reg, val);
	writeb(val, socket->base + 0x800 + reg);
	readb(socket->base + 0x800 + reg); /* PCI write posting... */
}