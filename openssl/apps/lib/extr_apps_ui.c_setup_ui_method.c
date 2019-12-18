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
 int /*<<< orphan*/  UI_OpenSSL () ; 
 int /*<<< orphan*/  UI_create_method (char*) ; 
 int /*<<< orphan*/  UI_method_set_closer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_method_set_opener (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_method_set_reader (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_method_set_writer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_null () ; 
 int /*<<< orphan*/  ui_close ; 
 int /*<<< orphan*/  ui_fallback_method ; 
 int /*<<< orphan*/  ui_method ; 
 int /*<<< orphan*/  ui_open ; 
 int /*<<< orphan*/  ui_read ; 
 int /*<<< orphan*/  ui_write ; 

int setup_ui_method(void)
{
    ui_fallback_method = UI_null();
#ifndef OPENSSL_NO_UI_CONSOLE
    ui_fallback_method = UI_OpenSSL();
#endif
    ui_method = UI_create_method("OpenSSL application user interface");
    UI_method_set_opener(ui_method, ui_open);
    UI_method_set_reader(ui_method, ui_read);
    UI_method_set_writer(ui_method, ui_write);
    UI_method_set_closer(ui_method, ui_close);
    return 0;
}