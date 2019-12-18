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
struct TYPE_4__ {int /*<<< orphan*/ * val; int /*<<< orphan*/ * key; } ;
typedef  TYPE_1__ xml_element_attr ;

/* Variables and functions */
 TYPE_1__* emalloc (int) ; 
 int /*<<< orphan*/ * estrdup (char const*) ; 

__attribute__((used)) static xml_element_attr* new_attr(const char* key, const char* val) {
	xml_element_attr* attr = emalloc(sizeof(xml_element_attr));
	if (attr) {
		attr->key = key ? estrdup(key) : NULL;
		attr->val = val ? estrdup(val) : NULL;
	}
	return attr;
}