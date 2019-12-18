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
struct TYPE_2__ {char const** array; int array_index; int array_size; int /*<<< orphan*/  sdb; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,char const*,char const*) ;scalar_t__ val; scalar_t__ key; } ;
typedef  TYPE_1__ LikeCallbackData ;

/* Variables and functions */
 scalar_t__ realloc (char const**,int) ; 
 int /*<<< orphan*/  sdb_match (char const*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*,char const*) ; 

__attribute__((used)) static int like_cb(void *user, const char *k, const char *v) {
	LikeCallbackData *lcd = user;
	if (!user) {
		return 0;
	}
	if (k && lcd->key && !sdb_match (k, lcd->key)) {
		return 1;
	}
	if (v && lcd->val && !sdb_match (v, lcd->val)) {
		return 1;
	}
	if (lcd->array) {
		int idx = lcd->array_index;
		int newsize = lcd->array_size + sizeof (char*) * 2;
		const char **newarray = (const char **)realloc (lcd->array, newsize);
		if (!newarray) {
			return 0;
		}
		lcd->array = newarray;
		lcd->array_size = newsize;
		// concatenate in array
		lcd->array[idx] = k;
		lcd->array[idx + 1] = v;
		lcd->array[idx + 2] = NULL;
		lcd->array[idx + 3] = NULL;
		lcd->array_index = idx+2;
	} else {
		if (lcd->cb) {
			lcd->cb (lcd->sdb, k, v);
		}
	}
	return 1;
}