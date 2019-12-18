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
 int CONF_parse_list (char const*,char,int,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  mask_cb ; 

int ASN1_str2mask(const char *str, unsigned long *pmask)
{
    *pmask = 0;
    return CONF_parse_list(str, '|', 1, mask_cb, pmask);
}