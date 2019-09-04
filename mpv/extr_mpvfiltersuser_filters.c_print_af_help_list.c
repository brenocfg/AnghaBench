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
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  print_lavfi_help_list (struct mp_log*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_af_help_list(struct mp_log *log)
{
    print_lavfi_help_list(log, AVMEDIA_TYPE_AUDIO);
}