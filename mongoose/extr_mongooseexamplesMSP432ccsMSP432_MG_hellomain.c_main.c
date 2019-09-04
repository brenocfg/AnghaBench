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

/* Variables and functions */
 int /*<<< orphan*/  Board_initGPIO () ; 
 int /*<<< orphan*/  Board_initGeneral () ; 
 int /*<<< orphan*/  Board_initWiFi () ; 
 int /*<<< orphan*/  LL_ERROR ; 
 int /*<<< orphan*/  LL_INFO ; 
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MGOS_TASK_PRIORITY ; 
 int /*<<< orphan*/  MG_TASK_STACK_SIZE ; 
 int /*<<< orphan*/  _IOLBF ; 
 int /*<<< orphan*/  cs_log_set_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs_log_set_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_init ; 
 int /*<<< orphan*/  mg_start_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_start () ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

int main(void) {
  Board_initGeneral();
  Board_initGPIO();
  Board_initWiFi();

  setvbuf(stdout, NULL, _IOLBF, 0);
  setvbuf(stderr, NULL, _IOLBF, 0);
  cs_log_set_level(LL_INFO);
  cs_log_set_file(stdout);

  if (!mg_start_task(MGOS_TASK_PRIORITY, MG_TASK_STACK_SIZE, mg_init)) {
    LOG(LL_ERROR, ("Error starting Mongoose task"));
    return 1;
  }

  osi_start();

  return 0;
}