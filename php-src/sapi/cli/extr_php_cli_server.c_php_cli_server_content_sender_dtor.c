#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ php_cli_server_content_sender ;

/* Variables and functions */
 int /*<<< orphan*/  php_cli_server_buffer_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void php_cli_server_content_sender_dtor(php_cli_server_content_sender *sender) /* {{{ */
{
	php_cli_server_buffer_dtor(&sender->buffer);
}