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
typedef  int /*<<< orphan*/  m_option_t ;

/* Variables and functions */
 char* mp_imgfmt_to_name (int) ; 
 char* talloc_strdup (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static char *print_imgfmt(const m_option_t *opt, const void *val)
{
    int fmt = *(int *)val;
    return talloc_strdup(NULL, fmt ? mp_imgfmt_to_name(fmt) : "no");
}