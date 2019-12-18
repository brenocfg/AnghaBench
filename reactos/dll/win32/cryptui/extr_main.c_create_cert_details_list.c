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
struct detail_data {int dummy; } ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  create_listview_columns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_show_list (int /*<<< orphan*/ ,struct detail_data*) ; 
 int /*<<< orphan*/  set_fields_selection (int /*<<< orphan*/ ,struct detail_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void create_cert_details_list(HWND hwnd, struct detail_data *data)
{
    create_show_list(hwnd, data);
    create_listview_columns(hwnd);
    set_fields_selection(hwnd, data, 0);
}