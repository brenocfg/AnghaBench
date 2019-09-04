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
struct TYPE_3__ {int /*<<< orphan*/  card; scalar_t__ chan; } ;
typedef  TYPE_1__ port_t ;

/* Variables and functions */
 int /*<<< orphan*/  IER0 ; 
 int sca_inl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sca_outl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void disable_intr(port_t *port)
{
	sca_outl(sca_inl(IER0, port->card) &
		 (port->chan ? 0x00FF00FF : 0xFF00FF00), IER0, port->card);
}