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
struct stat {int /*<<< orphan*/  st_size; } ;
struct perf_entry_data {int /*<<< orphan*/  topic; int /*<<< orphan*/  outfp; } ;
struct FTW {int level; int base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FTW_D ; 
 int FTW_F ; 
 scalar_t__ add_topic (char*) ; 
 scalar_t__ close_table ; 
 int /*<<< orphan*/  eventsfp ; 
 char* file_name_to_table_name (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_topic () ; 
 int /*<<< orphan*/  is_json_file (char*) ; 
 scalar_t__ is_leaf_dir (char const*) ; 
 int json_events (char const*,int /*<<< orphan*/ ,struct perf_entry_data*) ; 
 int /*<<< orphan*/  mapfile ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  print_events_table_entry ; 
 int /*<<< orphan*/  print_events_table_prefix (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_events_table_suffix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prog ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

__attribute__((used)) static int process_one_file(const char *fpath, const struct stat *sb,
			    int typeflag, struct FTW *ftwbuf)
{
	char *tblname, *bname;
	int is_dir  = typeflag == FTW_D;
	int is_file = typeflag == FTW_F;
	int level   = ftwbuf->level;
	int err = 0;

	if (level == 2 && is_dir) {
		/*
		 * For level 2 directory, bname will include parent name,
		 * like vendor/platform. So search back from platform dir
		 * to find this.
		 */
		bname = (char *) fpath + ftwbuf->base - 2;
		for (;;) {
			if (*bname == '/')
				break;
			bname--;
		}
		bname++;
	} else
		bname = (char *) fpath + ftwbuf->base;

	pr_debug("%s %d %7jd %-20s %s\n",
		 is_file ? "f" : is_dir ? "d" : "x",
		 level, sb->st_size, bname, fpath);

	/* base dir or too deep */
	if (level == 0 || level > 3)
		return 0;


	/* model directory, reset topic */
	if ((level == 1 && is_dir && is_leaf_dir(fpath)) ||
	    (level == 2 && is_dir)) {
		if (close_table)
			print_events_table_suffix(eventsfp);

		/*
		 * Drop file name suffix. Replace hyphens with underscores.
		 * Fail if file name contains any alphanum characters besides
		 * underscores.
		 */
		tblname = file_name_to_table_name(bname);
		if (!tblname) {
			pr_info("%s: Error determining table name for %s\n", prog,
				bname);
			return -1;
		}

		print_events_table_prefix(eventsfp, tblname);
		return 0;
	}

	/*
	 * Save the mapfile name for now. We will process mapfile
	 * after processing all JSON files (so we can write out the
	 * mapping table after all PMU events tables).
	 *
	 */
	if (level == 1 && is_file) {
		if (!strcmp(bname, "mapfile.csv")) {
			mapfile = strdup(fpath);
			return 0;
		}

		pr_info("%s: Ignoring file %s\n", prog, fpath);
		return 0;
	}

	/*
	 * If the file name does not have a .json extension,
	 * ignore it. It could be a readme.txt for instance.
	 */
	if (is_file) {
		if (!is_json_file(bname)) {
			pr_info("%s: Ignoring file without .json suffix %s\n", prog,
				fpath);
			return 0;
		}
	}

	if (level > 1 && add_topic(bname))
		return -ENOMEM;

	/*
	 * Assume all other files are JSON files.
	 *
	 * If mapfile refers to 'power7_core.json', we create a table
	 * named 'power7_core'. Any inconsistencies between the mapfile
	 * and directory tree could result in build failure due to table
	 * names not being found.
	 *
	 * Atleast for now, be strict with processing JSON file names.
	 * i.e. if JSON file name cannot be mapped to C-style table name,
	 * fail.
	 */
	if (is_file) {
		struct perf_entry_data data = {
			.topic = get_topic(),
			.outfp = eventsfp,
		};

		err = json_events(fpath, print_events_table_entry, &data);

		free(data.topic);
	}

	return err;
}