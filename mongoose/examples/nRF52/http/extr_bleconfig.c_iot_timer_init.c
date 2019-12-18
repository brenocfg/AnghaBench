#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  list_of_clients ;
struct TYPE_4__ {int member_0; TYPE_2__ const* member_1; } ;
typedef  TYPE_1__ iot_timer_clients_list_t ;
struct TYPE_5__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ iot_timer_client_t ;

/* Variables and functions */
 int /*<<< orphan*/  APP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APP_TIMER_PRESCALER ; 
 int /*<<< orphan*/  APP_TIMER_TICKS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  COMMISSIONING_TICK_INTERVAL_SEC 133 
 int /*<<< orphan*/  IOT_TIMER_RESOLUTION_IN_MS ; 
#define  LED_BLINK_INTERVAL_MS 132 
#define  LWIP_SYS_TICK_MS 131 
 int /*<<< orphan*/  SEC_TO_MILLISEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  app_timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  blink_timeout_handler 130 
#define  commissioning_time_tick 129 
 int /*<<< orphan*/  iot_timer_client_list_set (TYPE_1__ const*) ; 
 int /*<<< orphan*/  m_iot_timer_tick_src_id ; 
#define  system_timer_callback 128 

__attribute__((used)) static void iot_timer_init(void)
{
  uint32_t err_code;

  static const iot_timer_client_t list_of_clients[] =
  {
    {system_timer_callback,   LWIP_SYS_TICK_MS},
#ifdef COMMISSIONING_ENABLED
    {blink_timeout_handler,   LED_BLINK_INTERVAL_MS},
    {commissioning_time_tick, SEC_TO_MILLISEC(COMMISSIONING_TICK_INTERVAL_SEC)}
#endif // COMMISSIONING_ENABLED
  };

  // The list of IoT Timer clients is declared as a constant.
  static const iot_timer_clients_list_t iot_timer_clients =
  {
    (sizeof(list_of_clients) / sizeof(iot_timer_client_t)),
    &(list_of_clients[0]),
  };

  // Passing the list of clients to the IoT Timer module.
  err_code = iot_timer_client_list_set(&iot_timer_clients);
  APP_ERROR_CHECK(err_code);

  // Starting the app timer instance that is the tick source for the IoT Timer.
  err_code = app_timer_start(m_iot_timer_tick_src_id, \
      APP_TIMER_TICKS(IOT_TIMER_RESOLUTION_IN_MS, APP_TIMER_PRESCALER), \
      NULL);
  APP_ERROR_CHECK(err_code);
}