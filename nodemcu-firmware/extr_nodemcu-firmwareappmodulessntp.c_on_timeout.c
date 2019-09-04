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
 int /*<<< orphan*/  sntp_dbg (char*) ; 
 int /*<<< orphan*/  sntp_dosend () ; 

__attribute__((used)) static void on_timeout (void *arg)
{
  (void)arg;
  sntp_dbg("sntp: timer\n");
  sntp_dosend ();
}