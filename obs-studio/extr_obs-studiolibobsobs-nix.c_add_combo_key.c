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
struct dstr {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  obs_key_t ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_cat (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_cat_dstr (struct dstr*,struct dstr*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_is_empty (struct dstr*) ; 
 int /*<<< orphan*/  obs_key_to_str (int /*<<< orphan*/ ,struct dstr*) ; 

__attribute__((used)) static inline void add_combo_key(obs_key_t key, struct dstr *str)
{
	struct dstr key_str = {0};

	obs_key_to_str(key, &key_str);

	if (!dstr_is_empty(&key_str)) {
		if (!dstr_is_empty(str)) {
			dstr_cat(str, " + ");
		}
		dstr_cat_dstr(str, &key_str);
	}

	dstr_free(&key_str);
}