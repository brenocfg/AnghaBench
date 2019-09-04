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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  ipv6_medium_instance_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_LOG (char*) ; 
 int /*<<< orphan*/  APP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LEDS_OFF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LEDS_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LED_ONE ; 
 int /*<<< orphan*/  LED_TWO ; 
 int /*<<< orphan*/  ipv6_medium_connectable_mode_enter (int /*<<< orphan*/ ) ; 
 TYPE_1__ m_ipv6_medium ; 

__attribute__((used)) static void connectable_mode_enter(void)
{
  uint32_t err_code = ipv6_medium_connectable_mode_enter(m_ipv6_medium.ipv6_medium_instance_id);
  APP_ERROR_CHECK(err_code);

  APPL_LOG("[APPL]: Physical layer in connectable mode.\r\n");
  LEDS_OFF(LED_TWO);
  LEDS_ON(LED_ONE);
}