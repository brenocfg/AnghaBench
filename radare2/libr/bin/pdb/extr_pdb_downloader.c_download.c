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
struct SPDBDownloader {TYPE_1__* opt; } ;
struct TYPE_2__ {char* dbg_file; char* symbol_store_path; char* guid; char* user_agent; char* symbol_server; scalar_t__ extract; } ;
typedef  TYPE_1__ SPDBDownloaderOpt ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (char*) ; 
 int /*<<< orphan*/  R_SYS_DIR ; 
 int /*<<< orphan*/  checkCurl () ; 
 scalar_t__ checkExtract () ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 char* r_file_dirname (char*) ; 
 int /*<<< orphan*/  r_file_rm (char*) ; 
 char* r_str_escape (char*) ; 
 char* r_str_newf (char const*,char const*,char*,char*,...) ; 
 scalar_t__ r_sys_cmd (char*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int download(struct SPDBDownloader *pd) {
	SPDBDownloaderOpt *opt = pd->opt;
	char *curl_cmd = NULL;
	char *extractor_cmd = NULL;
	char *abspath_to_archive = NULL;
	char *archive_name = NULL;
	size_t archive_name_len = 0;
	char *symbol_store_path = NULL;
	char *dbg_file = NULL;
	char *guid = NULL;
	char *archive_name_escaped  = NULL;
	char *user_agent = NULL;
	char *symbol_server = NULL;

	int res = 0;
	int cmd_ret;
	if (!opt->dbg_file || !*opt->dbg_file) {
		// no pdb debug file
		return 0;
	}
	if (!checkCurl ()) {
		return 0;
	}
	// dbg_file len is > 0
	archive_name_len = strlen (opt->dbg_file);
	archive_name = malloc (archive_name_len + 1);
	if (!archive_name) {
		return 0;
	}
	memcpy (archive_name, opt->dbg_file, archive_name_len + 1);
	archive_name[archive_name_len - 1] = '_';
	symbol_store_path = r_str_escape (opt->symbol_store_path);
	dbg_file = r_str_escape (opt->dbg_file);
	guid = r_str_escape (opt->guid);
	archive_name_escaped = r_str_escape (archive_name);
	user_agent = r_str_escape (opt->user_agent);
	symbol_server = r_str_escape (opt->symbol_server);

	if (checkExtract () || opt->extract == 0) {
		res = 1;
		abspath_to_archive = r_str_newf ("%s%s%s%s%s%s%s",
						    symbol_store_path, R_SYS_DIR,
						    dbg_file, R_SYS_DIR,
						    guid, R_SYS_DIR,
						    archive_name_escaped);

		curl_cmd = r_str_newf ("curl -sfLA \"%s\" \"%s/%s/%s/%s\" --create-dirs -o \"%s\"",
		                       user_agent,
		                       symbol_server,
							   dbg_file,
							   guid,
		                       archive_name_escaped,
		                       abspath_to_archive);
#if __WINDOWS__
		const char *cabextractor = "expand";
		const char *format = "%s %s %s";
		char *abspath_to_file = strdup (abspath_to_archive);
		abspath_to_file[strlen (abspath_to_file) - 1] = 'b';

		// extractor_cmd -> %1 %2 %3
		// %1 - 'expand'
		// %2 - absolute path to archive
		// %3 - absolute path to file that will be dearchive
		extractor_cmd = r_str_newf (format, cabextractor,
			abspath_to_archive, abspath_to_file);
#else
		const char *cabextractor = "cabextract";
		const char *format = "%s -d \"%s\" \"%s\"";
		char *abspath_to_dir = r_file_dirname (abspath_to_archive);
		// cabextract -d %1 %2
		// %1 - path to directory where to extract all files from cab archive
		// %2 - absolute path to cab archive
		extractor_cmd = r_str_newf (format, cabextractor, abspath_to_dir, abspath_to_archive);
		R_FREE (abspath_to_dir);
#endif
		eprintf ("Attempting to download compressed pdb in %s\n",abspath_to_archive);
		if ((cmd_ret = r_sys_cmd (curl_cmd) != 0)) {
			eprintf("curl exited with error %d\n", cmd_ret);
			res = 0;
		}
		eprintf ("Attempting to decompress pdb\n");
		if (opt->extract > 0) {
			if (res && ((cmd_ret = r_sys_cmd (extractor_cmd)) != 0)) {
				eprintf ("cab extractor exited with error %d\n", cmd_ret);
				res = 0;
			}
			r_file_rm (abspath_to_archive);
		}
		R_FREE (curl_cmd);
		R_FREE (abspath_to_archive);
	}
	if (res == 0) {
		eprintf ("Falling back to uncompressed pdb\n");
		res = 1;
		archive_name[archive_name_len - 1] = 'b';
		R_FREE (archive_name_escaped);
		archive_name_escaped = r_str_escape (archive_name);
		abspath_to_archive = r_str_newf("%s%s%s%s%s%s%s",
		    symbol_store_path, R_SYS_DIR,
		    dbg_file, R_SYS_DIR,
		    guid, R_SYS_DIR,
		    archive_name_escaped);

		curl_cmd = r_str_newf ("curl -sfLA \"%s\" \"%s/%s/%s/%s\" --create-dirs -o \"%s\"",
		                       opt->user_agent,
		                       opt->symbol_server,
		                       opt->dbg_file,
		                       opt->guid,
		                       archive_name_escaped,
		                       abspath_to_archive);
		eprintf ("Attempting to download uncompressed pdb in %s\n",abspath_to_archive);
		if ((cmd_ret = r_sys_cmd (curl_cmd) != 0)) {
			eprintf("curl exited with error %d\n", cmd_ret);
			res = 0;
		}
		R_FREE (curl_cmd);
		R_FREE (abspath_to_archive);
	}
	R_FREE (archive_name);
	R_FREE (extractor_cmd);
	R_FREE (symbol_store_path);
	R_FREE (dbg_file);
	R_FREE (guid);
	R_FREE (archive_name_escaped);
	R_FREE (user_agent);
	R_FREE (symbol_server);
	return res;
}