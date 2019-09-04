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
struct mp_log {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  print_help (struct mp_log*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void print_help_v(struct mp_log *log)
{
    print_help(log, AVMEDIA_TYPE_VIDEO, "video", "--vf=lavfi=[gradfun=20:30]");
}