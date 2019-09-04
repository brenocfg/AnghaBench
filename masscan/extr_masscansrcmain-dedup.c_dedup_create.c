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
struct DedupTable {int dummy; } ;

/* Variables and functions */
 struct DedupTable* CALLOC (int,int) ; 

struct DedupTable *
dedup_create(void)
{
    struct DedupTable *result;

    result = CALLOC(1, sizeof(*result));

    return result;
}