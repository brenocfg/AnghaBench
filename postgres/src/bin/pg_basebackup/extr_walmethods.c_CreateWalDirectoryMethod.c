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
struct TYPE_4__ {int /*<<< orphan*/  getlasterror; int /*<<< orphan*/  finish; int /*<<< orphan*/  existsfile; int /*<<< orphan*/  sync; int /*<<< orphan*/  close; int /*<<< orphan*/  get_file_size; int /*<<< orphan*/  get_current_pos; int /*<<< orphan*/  write; int /*<<< orphan*/  open_for_write; } ;
typedef  TYPE_1__ WalWriteMethod ;
struct TYPE_5__ {int compression; int sync; int /*<<< orphan*/  basedir; } ;
typedef  int /*<<< orphan*/  DirectoryMethodData ;

/* Variables and functions */
 int /*<<< orphan*/  dir_close ; 
 TYPE_2__* dir_data ; 
 int /*<<< orphan*/  dir_existsfile ; 
 int /*<<< orphan*/  dir_finish ; 
 int /*<<< orphan*/  dir_get_current_pos ; 
 int /*<<< orphan*/  dir_get_file_size ; 
 int /*<<< orphan*/  dir_getlasterror ; 
 int /*<<< orphan*/  dir_open_for_write ; 
 int /*<<< orphan*/  dir_sync ; 
 int /*<<< orphan*/  dir_write ; 
 void* pg_malloc0 (int) ; 
 int /*<<< orphan*/  pg_strdup (char const*) ; 

WalWriteMethod *
CreateWalDirectoryMethod(const char *basedir, int compression, bool sync)
{
	WalWriteMethod *method;

	method = pg_malloc0(sizeof(WalWriteMethod));
	method->open_for_write = dir_open_for_write;
	method->write = dir_write;
	method->get_current_pos = dir_get_current_pos;
	method->get_file_size = dir_get_file_size;
	method->close = dir_close;
	method->sync = dir_sync;
	method->existsfile = dir_existsfile;
	method->finish = dir_finish;
	method->getlasterror = dir_getlasterror;

	dir_data = pg_malloc0(sizeof(DirectoryMethodData));
	dir_data->compression = compression;
	dir_data->basedir = pg_strdup(basedir);
	dir_data->sync = sync;

	return method;
}