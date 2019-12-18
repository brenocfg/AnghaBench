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
typedef  int u8 ;
struct tomoyo_io_buffer {int dummy; } ;

/* Variables and functions */
 int const TOMOYO_CONFIG_WANT_GRANT_LOG ; 
 int const TOMOYO_CONFIG_WANT_REJECT_LOG ; 
 int /*<<< orphan*/  tomoyo_io_printf (struct tomoyo_io_buffer*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tomoyo_mode ; 
 int /*<<< orphan*/  tomoyo_yesno (int const) ; 

__attribute__((used)) static void tomoyo_print_config(struct tomoyo_io_buffer *head, const u8 config)
{
	tomoyo_io_printf(head, "={ mode=%s grant_log=%s reject_log=%s }\n",
			 tomoyo_mode[config & 3],
			 tomoyo_yesno(config & TOMOYO_CONFIG_WANT_GRANT_LOG),
			 tomoyo_yesno(config & TOMOYO_CONFIG_WANT_REJECT_LOG));
}