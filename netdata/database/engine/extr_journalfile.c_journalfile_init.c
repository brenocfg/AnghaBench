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
typedef  scalar_t__ uv_file ;
struct rrdengine_journalfile {struct rrdengine_datafile* datafile; scalar_t__ pos; scalar_t__ file; } ;
struct rrdengine_datafile {int dummy; } ;

/* Variables and functions */

void journalfile_init(struct rrdengine_journalfile *journalfile, struct rrdengine_datafile *datafile)
{
    journalfile->file = (uv_file)0;
    journalfile->pos = 0;
    journalfile->datafile = datafile;
}