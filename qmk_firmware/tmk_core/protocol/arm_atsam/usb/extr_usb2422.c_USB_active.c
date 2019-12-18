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
typedef  int uint16_t ;
struct TYPE_6__ {TYPE_2__* Group; } ;
struct TYPE_4__ {int reg; } ;
struct TYPE_5__ {TYPE_1__ IN; } ;

/* Variables and functions */
 TYPE_3__* PORT ; 
 size_t USB2422_HUB_ACTIVE_GROUP ; 
 int USB2422_HUB_ACTIVE_PIN ; 

uint16_t USB_active(void) { return (PORT->Group[USB2422_HUB_ACTIVE_GROUP].IN.reg & (1 << USB2422_HUB_ACTIVE_PIN)) != 0; }