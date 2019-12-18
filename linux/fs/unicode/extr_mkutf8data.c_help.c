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
 char* AGE_NAME ; 
 char* CCC_NAME ; 
 char* DATA_NAME ; 
 char* FOLD_NAME ; 
 char* NORM_NAME ; 
 char* PROP_NAME ; 
 char* TEST_NAME ; 
 char* UTF8_NAME ; 
 char* argv0 ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void help(void)
{
	printf("Usage: %s [options]\n", argv0);
	printf("\n");
	printf("This program creates an a data trie used for parsing and\n");
	printf("normalization of UTF-8 strings. The trie is derived from\n");
	printf("a set of input files from the Unicode character database\n");
	printf("found at: http://www.unicode.org/Public/UCD/latest/ucd/\n");
	printf("\n");
	printf("The generated tree supports two normalization forms:\n");
	printf("\n");
	printf("\tnfdi:\n");
	printf("\t- Apply unicode normalization form NFD.\n");
	printf("\t- Remove any Default_Ignorable_Code_Point.\n");
	printf("\n");
	printf("\tnfdicf:\n");
	printf("\t- Apply unicode normalization form NFD.\n");
	printf("\t- Remove any Default_Ignorable_Code_Point.\n");
	printf("\t- Apply a full casefold (C + F).\n");
	printf("\n");
	printf("These forms were chosen as being most useful when dealing\n");
	printf("with file names: NFD catches most cases where characters\n");
	printf("should be considered equivalent. The ignorables are mostly\n");
	printf("invisible, making names hard to type.\n");
	printf("\n");
	printf("The options to specify the files to be used are listed\n");
	printf("below with their default values, which are the names used\n");
	printf("by version 11.0.0 of the Unicode Character Database.\n");
	printf("\n");
	printf("The input files:\n");
	printf("\t-a %s\n", AGE_NAME);
	printf("\t-c %s\n", CCC_NAME);
	printf("\t-p %s\n", PROP_NAME);
	printf("\t-d %s\n", DATA_NAME);
	printf("\t-f %s\n", FOLD_NAME);
	printf("\t-n %s\n", NORM_NAME);
	printf("\n");
	printf("Additionally, the generated tables are tested using:\n");
	printf("\t-t %s\n", TEST_NAME);
	printf("\n");
	printf("Finally, the output file:\n");
	printf("\t-o %s\n", UTF8_NAME);
	printf("\n");
}