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
struct rrdengine_journalfile {scalar_t__ pos; struct rrdengine_journalfile* journalfile; } ;
struct rrdengine_instance {char* dbfiles_path; int /*<<< orphan*/  disk_space; } ;
struct rrdengine_datafile {scalar_t__ pos; struct rrdengine_datafile* journalfile; } ;
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 int RRDENG_PATH_MAX ; 
 int create_data_file (struct rrdengine_journalfile*) ; 
 int create_journal_file (struct rrdengine_journalfile*,struct rrdengine_journalfile*) ; 
 int /*<<< orphan*/  datafile_init (struct rrdengine_journalfile*,struct rrdengine_instance*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  datafile_list_insert (struct rrdengine_instance*,struct rrdengine_journalfile*) ; 
 int /*<<< orphan*/  destroy_data_file (struct rrdengine_journalfile*) ; 
 int /*<<< orphan*/  freez (struct rrdengine_journalfile*) ; 
 int /*<<< orphan*/  generate_datafilepath (struct rrdengine_journalfile*,char*,int) ; 
 int /*<<< orphan*/  generate_journalfilepath (struct rrdengine_journalfile*,char*,int) ; 
 int /*<<< orphan*/  info (char*,char*) ; 
 int /*<<< orphan*/  journalfile_init (struct rrdengine_journalfile*,struct rrdengine_journalfile*) ; 
 struct rrdengine_journalfile* mallocz (int) ; 

int create_new_datafile_pair(struct rrdengine_instance *ctx, unsigned tier, unsigned fileno)
{
    struct rrdengine_datafile *datafile;
    struct rrdengine_journalfile *journalfile;
    int ret;
    char path[RRDENG_PATH_MAX];

    info("Creating new data and journal files in path %s", ctx->dbfiles_path);
    datafile = mallocz(sizeof(*datafile));
    datafile_init(datafile, ctx, tier, fileno);
    ret = create_data_file(datafile);
    if (!ret) {
        generate_datafilepath(datafile, path, sizeof(path));
        info("Created data file \"%s\".", path);
    } else {
        goto error_after_datafile;
    }

    journalfile = mallocz(sizeof(*journalfile));
    datafile->journalfile = journalfile;
    journalfile_init(journalfile, datafile);
    ret = create_journal_file(journalfile, datafile);
    if (!ret) {
        generate_journalfilepath(datafile, path, sizeof(path));
        info("Created journal file \"%s\".", path);
    } else {
        goto error_after_journalfile;
    }
    datafile_list_insert(ctx, datafile);
    ctx->disk_space += datafile->pos + journalfile->pos;

    return 0;

error_after_journalfile:
    destroy_data_file(datafile);
    freez(journalfile);
error_after_datafile:
    freez(datafile);
    return ret;
}