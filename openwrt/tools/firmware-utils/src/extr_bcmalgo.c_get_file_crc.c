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
typedef  int /*<<< orphan*/  uint32_t ;
struct stat {scalar_t__ st_size; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fread (char*,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_buffer_crc (char*,scalar_t__) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 

uint32_t get_file_crc ( char* filename )
{
	struct stat buf;
	stat ( filename,&buf );
	char* filebuffer = malloc ( buf.st_size+10 );
	FILE* fd = fopen ( filename,"r" );
	fread ( filebuffer, 1, buf.st_size,fd );
	fclose ( fd );
	uint32_t crc = get_buffer_crc ( filebuffer,buf.st_size );
	free ( filebuffer );
	return crc;
}