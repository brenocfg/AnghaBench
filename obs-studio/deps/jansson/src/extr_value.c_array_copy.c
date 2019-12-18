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
typedef  int /*<<< orphan*/  json_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **,int /*<<< orphan*/ **,size_t) ; 

__attribute__((used)) static void array_copy(json_t **dest, size_t dpos,
                       json_t **src, size_t spos,
                       size_t count)
{
    memcpy(&dest[dpos], &src[spos], count * sizeof(json_t *));
}