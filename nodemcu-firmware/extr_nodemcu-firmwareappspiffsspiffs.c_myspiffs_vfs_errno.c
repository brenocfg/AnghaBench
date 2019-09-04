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
typedef  int /*<<< orphan*/  sint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPIFFS_errno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fs ; 

__attribute__((used)) static sint32_t myspiffs_vfs_errno( void ) {
  return SPIFFS_errno( &fs );
}