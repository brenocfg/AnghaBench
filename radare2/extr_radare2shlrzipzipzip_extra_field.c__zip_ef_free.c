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
struct zip_extra_field {struct zip_extra_field* data; struct zip_extra_field* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct zip_extra_field*) ; 

void
_zip_ef_free(struct zip_extra_field *ef)
{
    struct zip_extra_field *ef2;

    while (ef) {
	ef2 = ef->next;
	free(ef->data);
	free(ef);
	ef = ef2;
    }
}