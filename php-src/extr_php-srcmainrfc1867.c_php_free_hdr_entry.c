#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ value; scalar_t__ key; } ;
typedef  TYPE_1__ mime_header_entry ;

/* Variables and functions */
 int /*<<< orphan*/  efree (scalar_t__) ; 

__attribute__((used)) static void php_free_hdr_entry(mime_header_entry *h)
{
	if (h->key) {
		efree(h->key);
	}
	if (h->value) {
		efree(h->value);
	}
}