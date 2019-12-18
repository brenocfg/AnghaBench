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

/* Variables and functions */
 char* PG_VERSION ; 
 char* bin_path ; 
 char* bki_file ; 
 int /*<<< orphan*/  check_input (char*) ; 
 char* conf_file ; 
 scalar_t__ debug ; 
 char* desc_file ; 
 char* dictionary_file ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 char* features_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 
 char* hba_file ; 
 char* ident_file ; 
 char* info_schema_file ; 
 char* pg_data ; 
 int /*<<< orphan*/  set_input (char**,char*) ; 
 char* share_path ; 
 char* shdesc_file ; 
 scalar_t__ show_setting ; 
 int /*<<< orphan*/  stderr ; 
 char* system_views_file ; 
 char* username ; 

void
setup_data_file_paths(void)
{
	set_input(&bki_file, "postgres.bki");
	set_input(&desc_file, "postgres.description");
	set_input(&shdesc_file, "postgres.shdescription");
	set_input(&hba_file, "pg_hba.conf.sample");
	set_input(&ident_file, "pg_ident.conf.sample");
	set_input(&conf_file, "postgresql.conf.sample");
	set_input(&dictionary_file, "snowball_create.sql");
	set_input(&info_schema_file, "information_schema.sql");
	set_input(&features_file, "sql_features.txt");
	set_input(&system_views_file, "system_views.sql");

	if (show_setting || debug)
	{
		fprintf(stderr,
				"VERSION=%s\n"
				"PGDATA=%s\nshare_path=%s\nPGPATH=%s\n"
				"POSTGRES_SUPERUSERNAME=%s\nPOSTGRES_BKI=%s\n"
				"POSTGRES_DESCR=%s\nPOSTGRES_SHDESCR=%s\n"
				"POSTGRESQL_CONF_SAMPLE=%s\n"
				"PG_HBA_SAMPLE=%s\nPG_IDENT_SAMPLE=%s\n",
				PG_VERSION,
				pg_data, share_path, bin_path,
				username, bki_file,
				desc_file, shdesc_file,
				conf_file,
				hba_file, ident_file);
		if (show_setting)
			exit(0);
	}

	check_input(bki_file);
	check_input(desc_file);
	check_input(shdesc_file);
	check_input(hba_file);
	check_input(ident_file);
	check_input(conf_file);
	check_input(dictionary_file);
	check_input(info_schema_file);
	check_input(features_file);
	check_input(system_views_file);
}