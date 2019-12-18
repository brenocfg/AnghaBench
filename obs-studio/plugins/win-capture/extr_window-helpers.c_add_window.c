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
struct dstr {int /*<<< orphan*/  array; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  obs_property_t ;
typedef  int /*<<< orphan*/  (* add_window_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_cat (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_cat_dstr (struct dstr*,struct dstr*) ; 
 scalar_t__ dstr_cmp (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 scalar_t__ dstr_is_empty (struct dstr*) ; 
 int /*<<< orphan*/  dstr_printf (struct dstr*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_dstr (struct dstr*) ; 
 int /*<<< orphan*/  get_window_class (struct dstr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_window_exe (struct dstr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_window_title (struct dstr*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_microsoft_internal_window_exe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_property_list_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_window(obs_property_t *p, HWND hwnd, add_window_cb callback)
{
	struct dstr class = {0};
	struct dstr title = {0};
	struct dstr exe = {0};
	struct dstr encoded = {0};
	struct dstr desc = {0};

	if (!get_window_exe(&exe, hwnd))
		return;
	if (is_microsoft_internal_window_exe(exe.array)) {
		dstr_free(&exe);
		return;
	}

	get_window_title(&title, hwnd);
	if (dstr_cmp(&exe, "explorer.exe") == 0 && dstr_is_empty(&title)) {
		dstr_free(&exe);
		dstr_free(&title);
		return;
	}

	get_window_class(&class, hwnd);

	if (callback && !callback(title.array, class.array, exe.array)) {
		dstr_free(&title);
		dstr_free(&class);
		dstr_free(&exe);
		return;
	}

	dstr_printf(&desc, "[%s]: %s", exe.array, title.array);

	encode_dstr(&title);
	encode_dstr(&class);
	encode_dstr(&exe);

	dstr_cat_dstr(&encoded, &title);
	dstr_cat(&encoded, ":");
	dstr_cat_dstr(&encoded, &class);
	dstr_cat(&encoded, ":");
	dstr_cat_dstr(&encoded, &exe);

	obs_property_list_add_string(p, desc.array, encoded.array);

	dstr_free(&encoded);
	dstr_free(&desc);
	dstr_free(&class);
	dstr_free(&title);
	dstr_free(&exe);
}