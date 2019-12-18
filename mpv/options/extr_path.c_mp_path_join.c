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

/* Variables and functions */
 int /*<<< orphan*/  bstr0 (char const*) ; 
 char* mp_path_join_bstr (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *mp_path_join(void *talloc_ctx, const char *p1, const char *p2)
{
    return mp_path_join_bstr(talloc_ctx, bstr0(p1), bstr0(p2));
}