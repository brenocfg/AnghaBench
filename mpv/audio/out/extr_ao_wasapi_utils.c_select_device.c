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
typedef  int /*<<< orphan*/  wchar_t ;
struct mp_log {int dummy; } ;
struct device_desc {int /*<<< orphan*/  deviceID; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/ * LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  mp_verbose (struct mp_log*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * talloc_memdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int wcslen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static LPWSTR select_device(struct mp_log *l, struct device_desc *d)
{
    if (!d)
        return NULL;
    mp_verbose(l, "Selecting device \'%s\' (%s)\n", d->id, d->name);
    return talloc_memdup(NULL, d->deviceID,
                         (wcslen(d->deviceID) + 1) * sizeof(wchar_t));
}