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
struct mg_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_IF_LedOff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_IF_LedOn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_IF_LedToggle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LL_ERROR ; 
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MCU_RED_LED_GPIO ; 
 int sscanf (char*,char*,int*,int*) ; 

__attribute__((used)) static void process_command(struct mg_connection *nc, unsigned char *data,
                            size_t len) {
  // TODO(lsm): use proper JSON parser
  int cmd, val;
  if (sscanf((char *) data, "{\"t\":%d,\"v\":%d}", &cmd, &val) != 2) {
    LOG(LL_ERROR, ("Invalid request: %.*s", (int) len, data));
    return;
  }
  if (cmd == 1) {
    switch (val) {
      case '0': {
        GPIO_IF_LedOff(MCU_RED_LED_GPIO);
        break;
      }
      case '1': {
        GPIO_IF_LedOn(MCU_RED_LED_GPIO);
        break;
      }
      case '2': {
        GPIO_IF_LedToggle(MCU_RED_LED_GPIO);
        break;
      }
      default: {
        LOG(LL_ERROR, ("Invalid value: %.*s", (int) len, data));
        return;
      }
    }
  } else {
    LOG(LL_ERROR, ("Unknown command: %.*s", (int) len, data));
    return;
  }
}