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
typedef  int /*<<< orphan*/  PCONFIGURATION_COMPONENT_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  FldrCreateSystemKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

PCONFIGURATION_COMPONENT_DATA PpcPrepHwDetect() {
  PCONFIGURATION_COMPONENT_DATA SystemKey;

  /* Create the 'System' key */
  FldrCreateSystemKey(&SystemKey);

  printf("DetectHardware() Done\n");
  return SystemKey;
}