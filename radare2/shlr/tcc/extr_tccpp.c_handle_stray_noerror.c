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
struct TYPE_2__ {int /*<<< orphan*/  line_num; } ;

/* Variables and functions */
 char ch ; 
 TYPE_1__* file ; 
 int /*<<< orphan*/  inp () ; 

__attribute__((used)) static int handle_stray_noerror(void)
{
	while (ch == '\\') {
		inp ();
		if (ch == '\n') {
			file->line_num++;
			inp ();
		} else if (ch == '\r') {
			inp ();
			if (ch != '\n') {
				goto fail;
			}
			file->line_num++;
			inp ();
		} else {
fail:
			return 1;
		}
	}
	return 0;
}