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
typedef  int /*<<< orphan*/  TarMethodData ;
struct TYPE_5__ {int fd; int compression; int sync; char* zlibOut; void* tarfilename; } ;

/* Variables and functions */
 scalar_t__ ZLIB_OUT_SIZE ; 
 scalar_t__ pg_malloc (scalar_t__) ; 
 void* pg_malloc0 (int) ; 
 int /*<<< orphan*/  sprintf (void*,char*,char const*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  tar_close ; 
 TYPE_2__* tar_data ; 
 int /*<<< orphan*/  tar_existsfile ; 
 int /*<<< orphan*/  tar_finish ; 
 int /*<<< orphan*/  tar_get_current_pos ; 
 int /*<<< orphan*/  tar_get_file_size ; 
 int /*<<< orphan*/  tar_getlasterror ; 
 int /*<<< orphan*/  tar_open_for_write ; 
 int /*<<< orphan*/  tar_sync ; 
 int /*<<< orphan*/  tar_write ; 

WalWriteMethod *
CreateWalTarMethod(const char *tarbase, int compression, bool sync)
{
	WalWriteMethod *method;
	const char *suffix = (compression != 0) ? ".tar.gz" : ".tar";

	method = pg_malloc0(sizeof(WalWriteMethod));
	method->open_for_write = tar_open_for_write;
	method->write = tar_write;
	method->get_current_pos = tar_get_current_pos;
	method->get_file_size = tar_get_file_size;
	method->close = tar_close;
	method->sync = tar_sync;
	method->existsfile = tar_existsfile;
	method->finish = tar_finish;
	method->getlasterror = tar_getlasterror;

	tar_data = pg_malloc0(sizeof(TarMethodData));
	tar_data->tarfilename = pg_malloc0(strlen(tarbase) + strlen(suffix) + 1);
	sprintf(tar_data->tarfilename, "%s%s", tarbase, suffix);
	tar_data->fd = -1;
	tar_data->compression = compression;
	tar_data->sync = sync;
#ifdef HAVE_LIBZ
	if (compression)
		tar_data->zlibOut = (char *) pg_malloc(ZLIB_OUT_SIZE + 1);
#endif

	return method;
}