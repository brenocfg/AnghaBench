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
typedef  int /*<<< orphan*/  uint8_t ;
struct game_capture {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pipe_log(void *param, uint8_t *data, size_t size)
{
	struct game_capture *gc = param;
	if (data && size)
		info("%s", data);
}