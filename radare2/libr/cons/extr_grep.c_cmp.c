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
typedef  scalar_t__ ut64 ;

/* Variables and functions */
 scalar_t__ IS_DIGIT (char const) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ r_num_get (int /*<<< orphan*/ *,char const*) ; 
 char* r_str_trim_ro (void const*) ; 
 char* r_str_word_get0 (char*,int) ; 
 int r_str_word_set0 (char*) ; 
 int sorted_column ; 
 int strcmp (void const*,void const*) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int cmp(const void *a, const void *b) {
	char *da = NULL;
	char *db = NULL;
	const char *ca = r_str_trim_ro (a);
	const char *cb = r_str_trim_ro (b);
	if (!a || !b) {
		return (int) (size_t) ((char*) a - (char*) b);
	}
	if (sorted_column > 0) {
		da = strdup (ca);
		db = strdup (cb);
		int colsa = r_str_word_set0 (da);
		int colsb = r_str_word_set0 (db);
		ca = (colsa > sorted_column)? r_str_word_get0 (da, sorted_column): "";
		cb = (colsb > sorted_column)? r_str_word_get0 (db, sorted_column): "";
	}
	if (IS_DIGIT (*ca) && IS_DIGIT (*cb)) {
		ut64 na = r_num_get (NULL, ca);
		ut64 nb = r_num_get (NULL, cb);
		int ret = na > nb;
		free (da);
		free (db);
		return ret;
	}
	if (da && db) {
		int ret = strcmp (ca, cb);
		free (da);
		free (db);
		return ret;
	}
	free (da);
	free (db);
	return strcmp (a, b);
}