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
 int /*<<< orphan*/  wifi_promiscuous_enable (int) ; 
 int /*<<< orphan*/  wifi_set_channel (int) ; 

__attribute__((used)) static void start_actually_monitoring() {
  wifi_set_channel(1);
  wifi_promiscuous_enable(1);
}