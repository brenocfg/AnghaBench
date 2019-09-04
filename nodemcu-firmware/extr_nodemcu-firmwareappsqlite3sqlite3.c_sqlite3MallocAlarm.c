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
struct TYPE_2__ {scalar_t__ alarmThreshold; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 TYPE_1__ mem0 ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_release_memory (int) ; 

__attribute__((used)) static void sqlite3MallocAlarm(int nByte){
  if( mem0.alarmThreshold<=0 ) return;
  sqlite3_mutex_leave(mem0.mutex);
  sqlite3_release_memory(nByte);
  sqlite3_mutex_enter(mem0.mutex);
}