#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct rrdengine_instance* data; } ;
typedef  TYPE_3__ uv_work_t ;
struct TYPE_6__ {int /*<<< orphan*/ * data; } ;
struct rrdengine_worker_config {int /*<<< orphan*/  async; TYPE_2__ now_deleting; } ;
struct rrdengine_journalfile {unsigned int pos; struct rrdengine_journalfile* journalfile; } ;
struct TYPE_5__ {struct rrdengine_journalfile* first; } ;
struct rrdengine_instance {unsigned int disk_space; TYPE_1__ datafiles; struct rrdengine_worker_config worker_config; } ;
struct rrdengine_datafile {unsigned int pos; struct rrdengine_datafile* journalfile; } ;
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 int RRDENG_PATH_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  datafile_list_delete (struct rrdengine_instance*,struct rrdengine_journalfile*) ; 
 int destroy_data_file (struct rrdengine_journalfile*) ; 
 int destroy_journal_file (struct rrdengine_journalfile*,struct rrdengine_journalfile*) ; 
 int /*<<< orphan*/  freez (struct rrdengine_journalfile*) ; 
 int /*<<< orphan*/  generate_datafilepath (struct rrdengine_journalfile*,char*,int) ; 
 int /*<<< orphan*/  generate_journalfilepath (struct rrdengine_journalfile*,char*,int) ; 
 int /*<<< orphan*/  info (char*,...) ; 
 scalar_t__ uv_async_send (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void after_delete_old_data(uv_work_t *req, int status)
{
    struct rrdengine_instance *ctx = req->data;
    struct rrdengine_worker_config* wc = &ctx->worker_config;
    struct rrdengine_datafile *datafile;
    struct rrdengine_journalfile *journalfile;
    unsigned deleted_bytes, journalfile_bytes, datafile_bytes;
    int ret;
    char path[RRDENG_PATH_MAX];

    (void)status;
    datafile = ctx->datafiles.first;
    journalfile = datafile->journalfile;
    datafile_bytes = datafile->pos;
    journalfile_bytes = journalfile->pos;
    deleted_bytes = 0;

    info("Deleting data and journal file pair.");
    datafile_list_delete(ctx, datafile);
    ret = destroy_journal_file(journalfile, datafile);
    if (!ret) {
        generate_journalfilepath(datafile, path, sizeof(path));
        info("Deleted journal file \"%s\".", path);
        deleted_bytes += journalfile_bytes;
    }
    ret = destroy_data_file(datafile);
    if (!ret) {
        generate_datafilepath(datafile, path, sizeof(path));
        info("Deleted data file \"%s\".", path);
        deleted_bytes += datafile_bytes;
    }
    freez(journalfile);
    freez(datafile);

    ctx->disk_space -= deleted_bytes;
    info("Reclaimed %u bytes of disk space.", deleted_bytes);

    /* unfreeze command processing */
    wc->now_deleting.data = NULL;
    /* wake up event loop */
    assert(0 == uv_async_send(&wc->async));
}