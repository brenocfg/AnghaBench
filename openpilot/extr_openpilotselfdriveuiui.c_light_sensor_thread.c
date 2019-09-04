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
struct sensors_poll_device_t {int (* poll ) (struct sensors_poll_device_t*,TYPE_1__*,size_t const) ;int /*<<< orphan*/  (* setDelay ) (struct sensors_poll_device_t*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* activate ) (struct sensors_poll_device_t*,int,int) ;} ;
struct sensors_module_t {int (* get_sensors_list ) (struct sensors_module_t*,struct sensor_t const**) ;int /*<<< orphan*/  common; } ;
struct sensor_t {int dummy; } ;
struct TYPE_4__ {double light; } ;
typedef  TYPE_1__ sensors_event_t ;
typedef  int /*<<< orphan*/  hw_module_t ;
struct TYPE_5__ {double light_sensor; } ;
typedef  TYPE_2__ UIState ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_100 (char*,int) ; 
 int /*<<< orphan*/  SENSORS_HARDWARE_MODULE_ID ; 
 int /*<<< orphan*/  do_exit ; 
 int /*<<< orphan*/  hw_get_module (int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  ms2ns (int) ; 
 int /*<<< orphan*/  sensors_open (int /*<<< orphan*/ *,struct sensors_poll_device_t**) ; 
 int stub1 (struct sensors_module_t*,struct sensor_t const**) ; 
 int /*<<< orphan*/  stub2 (struct sensors_poll_device_t*,int,int) ; 
 int /*<<< orphan*/  stub3 (struct sensors_poll_device_t*,int,int) ; 
 int /*<<< orphan*/  stub4 (struct sensors_poll_device_t*,int,int /*<<< orphan*/ ) ; 
 int stub5 (struct sensors_poll_device_t*,TYPE_1__*,size_t const) ; 

__attribute__((used)) static void* light_sensor_thread(void *args) {
  int err;

  UIState *s = args;
  s->light_sensor = 0.0;

  struct sensors_poll_device_t* device;
  struct sensors_module_t* module;

  hw_get_module(SENSORS_HARDWARE_MODULE_ID, (hw_module_t const**)&module);
  sensors_open(&module->common, &device);

  // need to do this
  struct sensor_t const* list;
  int count = module->get_sensors_list(module, &list);

  int SENSOR_LIGHT = 7;

  device->activate(device, SENSOR_LIGHT, 0);
  device->activate(device, SENSOR_LIGHT, 1);
  device->setDelay(device, SENSOR_LIGHT, ms2ns(100));

  while (!do_exit) {
    static const size_t numEvents = 1;
    sensors_event_t buffer[numEvents];

    int n = device->poll(device, buffer, numEvents);
    if (n < 0) {
      LOG_100("light_sensor_poll failed: %d", n);
    }
    if (n > 0) {
      s->light_sensor = buffer[0].light;
    }
  }

  return NULL;
}