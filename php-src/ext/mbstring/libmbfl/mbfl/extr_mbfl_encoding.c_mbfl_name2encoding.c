#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ *** aliases; int /*<<< orphan*/ * mime_name; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ mbfl_encoding ;

/* Variables and functions */
 TYPE_1__** mbfl_encoding_ptr_list ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ *,char const*) ; 

const mbfl_encoding *
mbfl_name2encoding(const char *name)
{
	const mbfl_encoding *encoding;
	int i, j;

	if (name == NULL) {
		return NULL;
	}

 	i = 0;
 	while ((encoding = mbfl_encoding_ptr_list[i++]) != NULL){
		if (strcasecmp(encoding->name, name) == 0) {
			return encoding;
		}
	}

 	/* serch MIME charset name */
 	i = 0;
 	while ((encoding = mbfl_encoding_ptr_list[i++]) != NULL) {
		if (encoding->mime_name != NULL) {
			if (strcasecmp(encoding->mime_name, name) == 0) {
				return encoding;
			}
		}
	}

 	/* serch aliases */
 	i = 0;
 	while ((encoding = mbfl_encoding_ptr_list[i++]) != NULL) {
		if (encoding->aliases != NULL) {
 			j = 0;
 			while ((*encoding->aliases)[j] != NULL) {
				if (strcasecmp((*encoding->aliases)[j], name) == 0) {
					return encoding;
				}
				j++;
			}
		}
	}

	return NULL;
}