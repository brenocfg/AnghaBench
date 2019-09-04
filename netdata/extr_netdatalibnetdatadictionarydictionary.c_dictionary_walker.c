#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__** avl_link; } ;
typedef  TYPE_1__ avl ;
struct TYPE_5__ {void* value; } ;
typedef  TYPE_2__ NAME_VALUE ;

/* Variables and functions */

__attribute__((used)) static int dictionary_walker(avl *a, int (*callback)(void *entry, void *data), void *data) {
    int total = 0, ret = 0;

    if(a->avl_link[0]) {
        ret = dictionary_walker(a->avl_link[0], callback, data);
        if(ret < 0) return ret;
        total += ret;
    }

    ret = callback(((NAME_VALUE *)a)->value, data);
    if(ret < 0) return ret;
    total += ret;

    if(a->avl_link[1]) {
        ret = dictionary_walker(a->avl_link[1], callback, data);
        if (ret < 0) return ret;
        total += ret;
    }

    return total;
}