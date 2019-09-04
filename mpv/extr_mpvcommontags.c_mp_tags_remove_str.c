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
struct mp_tags {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bstr0 (char const*) ; 
 int /*<<< orphan*/  mp_tags_remove_bstr (struct mp_tags*,int /*<<< orphan*/ ) ; 

void mp_tags_remove_str(struct mp_tags *tags, const char *key)
{
    mp_tags_remove_bstr(tags, bstr0(key));
}