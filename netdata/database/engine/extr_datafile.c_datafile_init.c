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
typedef  scalar_t__ uv_file ;
struct rrdengine_instance {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * last; int /*<<< orphan*/  first; } ;
struct rrdengine_datafile {unsigned int tier; unsigned int fileno; struct rrdengine_instance* ctx; int /*<<< orphan*/ * next; int /*<<< orphan*/ * journalfile; TYPE_1__ extents; scalar_t__ pos; scalar_t__ file; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void datafile_init(struct rrdengine_datafile *datafile, struct rrdengine_instance *ctx,
                          unsigned tier, unsigned fileno)
{
    assert(tier == 1);
    datafile->tier = tier;
    datafile->fileno = fileno;
    datafile->file = (uv_file)0;
    datafile->pos = 0;
    datafile->extents.first = datafile->extents.last = NULL; /* will be populated by journalfile */
    datafile->journalfile = NULL;
    datafile->next = NULL;
    datafile->ctx = ctx;
}