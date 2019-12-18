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
struct TYPE_5__ {int len; char* start; } ;
typedef  TYPE_1__ bstr ;

/* Variables and functions */
 int /*<<< orphan*/  BSTR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ bstr_endswith0 (TYPE_1__,char*) ; 
 int /*<<< orphan*/  bstr_splice (TYPE_1__,int /*<<< orphan*/ ,int) ; 
 char* talloc_asprintf (void*,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char *replace_idx_ext(void *ta_ctx, bstr f)
{
    if (f.len < 4 || f.start[f.len - 4] != '.')
        return NULL;
    char *ext = bstr_endswith0(f, "IDX") ? "SUB" : "sub"; // match case
    return talloc_asprintf(ta_ctx, "%.*s.%s", BSTR_P(bstr_splice(f, 0, -4)), ext);
}