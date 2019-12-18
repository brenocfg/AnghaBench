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
struct dstr {scalar_t__* array; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 scalar_t__* strdepad (scalar_t__*) ; 
 int /*<<< orphan*/  strlen (scalar_t__*) ; 

void dstr_depad(struct dstr *str)
{
	if (str->array) {
		str->array = strdepad(str->array);
		if (*str->array)
			str->len = strlen(str->array);
		else
			dstr_free(str);
	}
}