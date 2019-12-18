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
 int PG_DIR_MODE_GROUP ; 
 int PG_DIR_MODE_OWNER ; 
 int /*<<< orphan*/  PG_FILE_MODE_GROUP ; 
 int /*<<< orphan*/  PG_FILE_MODE_OWNER ; 
 int /*<<< orphan*/  PG_MODE_MASK_GROUP ; 
 int /*<<< orphan*/  PG_MODE_MASK_OWNER ; 
 int pg_dir_create_mode ; 
 int /*<<< orphan*/  pg_file_create_mode ; 
 int /*<<< orphan*/  pg_mode_mask ; 

void
SetDataDirectoryCreatePerm(int dataDirMode)
{
	/* If the data directory mode has group access */
	if ((PG_DIR_MODE_GROUP & dataDirMode) == PG_DIR_MODE_GROUP)
	{
		pg_dir_create_mode = PG_DIR_MODE_GROUP;
		pg_file_create_mode = PG_FILE_MODE_GROUP;
		pg_mode_mask = PG_MODE_MASK_GROUP;
	}
	/* Else use default permissions */
	else
	{
		pg_dir_create_mode = PG_DIR_MODE_OWNER;
		pg_file_create_mode = PG_FILE_MODE_OWNER;
		pg_mode_mask = PG_MODE_MASK_OWNER;
	}
}