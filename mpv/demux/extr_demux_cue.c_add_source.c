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
struct timeline {int /*<<< orphan*/  num_sources; int /*<<< orphan*/  sources; } ;
struct demuxer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct timeline*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct demuxer*) ; 

__attribute__((used)) static void add_source(struct timeline *tl, struct demuxer *d)
{
    MP_TARRAY_APPEND(tl, tl->sources, tl->num_sources, d);
}