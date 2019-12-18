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
 int SQLITE_OK ; 
 int /*<<< orphan*/  esp8266Vfs ; 
 int /*<<< orphan*/  sqlite3_vfs_register (int /*<<< orphan*/ *,int) ; 

int sqlite3_os_init(void){
  sqlite3_vfs_register(&esp8266Vfs, 1);
  return SQLITE_OK;
}