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
 int /*<<< orphan*/  APP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eui64_local_iid ; 
 int /*<<< orphan*/  ipv6_medium_eui64_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lwip_init () ; 
 TYPE_1__ m_ipv6_medium ; 
 int /*<<< orphan*/  nrf_driver_init () ; 
 int /*<<< orphan*/  nrf_mem_init () ; 

__attribute__((used)) static void ip_stack_init(void)
{
  uint32_t err_code;

  err_code = ipv6_medium_eui64_get(m_ipv6_medium.ipv6_medium_instance_id, \
      &eui64_local_iid);
  APP_ERROR_CHECK(err_code);

  err_code = nrf_mem_init();
  APP_ERROR_CHECK(err_code);

  //Initialize LwIP stack.
  lwip_init();

  //Initialize LwIP stack driver.
  err_code = nrf_driver_init();
  APP_ERROR_CHECK(err_code);
}