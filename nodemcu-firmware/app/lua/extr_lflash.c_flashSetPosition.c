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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curOffset ; 
 char* flashPosition () ; 

__attribute__((used)) static char *flashSetPosition(uint32_t offset){
  NODE_DBG("flashSetPosition(%04x)\n", offset);
  curOffset = offset;
  return flashPosition();
}