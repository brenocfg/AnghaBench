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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  exptime; } ;
typedef  TYPE_1__ item ;
typedef  int /*<<< orphan*/  conn ;

/* Variables and functions */
 int /*<<< orphan*/  DO_UPDATE ; 
 TYPE_1__* do_item_get (char const*,size_t,int /*<<< orphan*/  const,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

item *do_item_touch(const char *key, size_t nkey, uint32_t exptime,
                    const uint32_t hv, conn *c) {
    item *it = do_item_get(key, nkey, hv, c, DO_UPDATE);
    if (it != NULL) {
        it->exptime = exptime;
    }
    return it;
}