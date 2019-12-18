#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  message; } ;
struct Fortune {TYPE_1__ item; } ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fortune_compare(const void *a, const void *b)
{
    const struct Fortune *fortune_a = (const struct Fortune *)a;
    const struct Fortune *fortune_b = (const struct Fortune *)b;
    size_t a_len = strlen(fortune_a->item.message);
    size_t b_len = strlen(fortune_b->item.message);

    if (!a_len || !b_len)
        return a_len > b_len;

    size_t min_len = a_len < b_len ? a_len : b_len;
    int cmp = memcmp(fortune_a->item.message, fortune_b->item.message, min_len);
    if (cmp == 0)
        return a_len > b_len;

    return cmp > 0;
}