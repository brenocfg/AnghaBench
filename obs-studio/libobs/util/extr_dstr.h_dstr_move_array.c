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
struct dstr {char* array; scalar_t__ len; scalar_t__ capacity; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static inline void dstr_move_array(struct dstr *dst, char *str)
{
	dstr_free(dst);
	dst->array = str;
	dst->len = (!str) ? 0 : strlen(str);
	dst->capacity = dst->len + 1;
}