#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ len; } ;
typedef  TYPE_1__ bstr ;

/* Variables and functions */
 int /*<<< orphan*/  bstr0 (char*) ; 
 int /*<<< orphan*/  bstr_split_tok (int /*<<< orphan*/ ,char*,TYPE_1__*,TYPE_1__*) ; 
 char* bstrto0 (void*,TYPE_1__) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void split_ao_device(void *tmp, char *opt, char **out_ao, char **out_dev)
{
    *out_ao = NULL;
    *out_dev = NULL;
    if (!opt)
        return;
    if (!opt[0] || strcmp(opt, "auto") == 0)
        return;
    // Split on "/". If "/" is the final character, or absent, out_dev is NULL.
    bstr b_dev, b_ao;
    bstr_split_tok(bstr0(opt), "/", &b_ao, &b_dev);
    if (b_dev.len > 0)
        *out_dev = bstrto0(tmp, b_dev);
    *out_ao = bstrto0(tmp, b_ao);
}