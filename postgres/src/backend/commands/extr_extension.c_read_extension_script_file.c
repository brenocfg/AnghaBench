#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int encoding; } ;
typedef  TYPE_1__ ExtensionControlFile ;

/* Variables and functions */
 int GetDatabaseEncoding () ; 
 char* pg_any_to_server (char*,int,int) ; 
 int /*<<< orphan*/  pg_verify_mbstr_len (int,char*,int,int) ; 
 char* read_whole_file (char const*,int*) ; 

__attribute__((used)) static char *
read_extension_script_file(const ExtensionControlFile *control,
						   const char *filename)
{
	int			src_encoding;
	char	   *src_str;
	char	   *dest_str;
	int			len;

	src_str = read_whole_file(filename, &len);

	/* use database encoding if not given */
	if (control->encoding < 0)
		src_encoding = GetDatabaseEncoding();
	else
		src_encoding = control->encoding;

	/* make sure that source string is valid in the expected encoding */
	pg_verify_mbstr_len(src_encoding, src_str, len, false);

	/*
	 * Convert the encoding to the database encoding. read_whole_file
	 * null-terminated the string, so if no conversion happens the string is
	 * valid as is.
	 */
	dest_str = pg_any_to_server(src_str, len, src_encoding);

	return dest_str;
}