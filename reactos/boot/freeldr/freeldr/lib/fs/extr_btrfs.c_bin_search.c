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
typedef  int (* cmp_func ) (void*,void*) ;
typedef  int /*<<< orphan*/  UCHAR ;

/* Variables and functions */

__attribute__((used)) static int bin_search(void *ptr, int item_size, void *cmp_item, cmp_func func,
                      int min, int max, int *slot)
{
    int low = min;
    int high = max;
    int mid;
    int ret;
    unsigned long offset;
    UCHAR *item;

    while (low < high)
    {
        mid = (low + high) / 2;
        offset = mid * item_size;

        item = (UCHAR *) ptr + offset;
        ret = func((void *) item, cmp_item);

        if (ret < 0)
        {
            low = mid + 1;
        }
        else if (ret > 0)
        {
            high = mid;
        }
        else
        {
            *slot = mid;
            return 0;
        }
    }
    *slot = low;
    return 1;
}